#include "tetris.h"

///// DEFINITIONS /////

int const FRAME_TIME = 15; // milliseconds
bgr const DEAD_COLOR = BGR(128, 128, 128);
bgr const TETRO_COLOR = BGR(192, 96, 96);

INT32 const TILE_WIDTH = 16, TILE_HEIGHT = 16;

///// LOGIC /////

/**
 * \brief
 * Converts a grid-local tile coordinate into a grid array index.
 */
int tile_index(game_state const * const s, vec2 p) {
  return p.x + p.y * s->grid_size.x;
}

/**
 * \brief
 * Reads tile data from the grid at the given position.
 */
tile get_tile(game_state const * const s, vec2 p) {
  return s->grid[tile_index(s, p)];
}

tile * ref_tile(game_state * const s, vec2 p) {
  return &s->grid[tile_index(s, p)];
}

/**
 * \brief
 * Decides whether the given point is in the grid's bounds.
 */
int grid_bounds_check(game_state const * const s, vec2 p) {
  return 0 <= p.x && p.x < s->grid_size.x
    && 0 <= p.y && p.y < s->grid_size.y;
}

/**
 * \brief
 * Decides whether the given tetromino is valid in the game state, i.e.
 * it is not out-of-bounds and does not overlap with any dead blocks.
 */
int is_tetromino_valid(game_state const * const s) {
  //
  for(int i = 0; i < TETROMINO_GRID_LENGTH; i++) {
    // skip empty blocks
    if(!s->current_tetromino.template->data[i])
      continue;

    // convert to grid coordinates and check if the grid cell is
    // nonempty
    vec2 p = tetro_index_to_tetro_local(i);
    vec2 q = tetro_local_to_grid_local(&s->current_tetromino, p);

    // check if out of bounds
    if(!grid_bounds_check(s, q))
      return 0;

    if(get_tile(s, q))
      // the tile is true => there is a dead block here, and we're
      // overlapping it
      return 0;
  }

  return 1;
}

/**
 * \brief
 * Gets the next tetromino.
 * Should be called after the player's tetromino has fallen and been frozen.
 *
 * Copies the tetromino referred to by `next_tetromino` into
 * `current_tetromino` and pumps the PRNG to get a new value for
 * `next_tetromino`.
 */
void next_tetromino(game_state * const s) {
  // get a random index 
  UINT32 i = next_uint32(s->rng) % TETROMINO_COUNT;
  s->current_tetromino = (tetromino) {
    .template = s->next_tetromino,
    .rotation = ZERO_ROTATION,
    .position = (vec2) { .x = 4, .y = 0 }
  };
  s->next_tetromino = TETROMINOES[i];

  Print(L"DEBUG: next tetromino is %d\n", i);
}

game_state
make_initial_state(int * const ok, LFB * const lfb, RNG * const rng) {
  int _ok;
  
  game_state s = {
    .lfb = lfb,
    .rng = rng,
    .timer = make_timer(&_ok, FRAME_TIME),
    .next_tetromino = &tetro_l,
    .frame_number = 0,
    .tile_size = (vec2) { .x = TILE_WIDTH, .y = TILE_HEIGHT },
    .grid_size = (vec2) { .x = GRID_WIDTH, .y = GRID_HEIGHT },
    .grid_origin = (vec2) {
      .x = lfb->width / 2 - GRID_WIDTH * TILE_WIDTH / 2,
      .y = lfb->height / 2 - GRID_HEIGHT * TILE_HEIGHT / 2
    },
    .tick_period = INITIAL_TICK_PERIOD,
    .last_tick = 0,
    .eliminated_rows = 0
  };

  Print(
    L"DEBUG: grid origin is (0, 0)\n",
    s.grid_origin.x,
    s.grid_origin.y);

  if(!_ok) {
    *ok = _ok;
    return s;
  }
  
  for(int i = 0; i < s.grid_size.x * s.grid_size.y; i++) {
    s.grid[i] = EMPTY;
  }

  *ok = 1;

  next_tetromino(&s);
  next_tetromino(&s);

  return s;
}

/**
 * \brief
 * Freezes the player's tetromino into the grid.
 */
void freeze_tetromino(game_state * const s) {
  for(UINT8 i = 0; i < TETROMINO_GRID_LENGTH; i++) {
    // skip if there's no block at that index
    if(!s->current_tetromino.template->data[i])
      continue;

    // otherwise, figure out what position in the grid that's supposed to be
    vec2 p = tetro_index_to_tetro_local(i);
    vec2 q = tetro_local_to_grid_local(&s->current_tetromino, p);

    // q is a valid position into the grid
    *ref_tile(s, q) = 1;
  }
}

void tick(game_state * const s) {
  Print(L"DEBUG: tick!\n");
  s->current_tetromino.position.y++;
  if(!is_tetromino_valid(s)) {
    s->current_tetromino.position.y--;
    freeze_tetromino(s);
    next_tetromino(s);
  }
}

int should_tick(game_state * const s) {
  return s->frame_number - s->last_tick >= s->tick_period;
}

/**
 * \brief
 * Removes row `y` from the grid, shifting earlier rows down.
 */
void eliminate_row(game_state * const s, int y) {
  while(y --> 0) {
    for(int x = 0; x < s->grid_size.x; x++) {
      tile *src = ref_tile(s, (vec2) { x, y }),
        *dst = ref_tile(s, (vec2) {x, y + 1});
      *dst = *src;
    }
  }
}

void check_full_rows(game_state * const s) {
  Print(L"DEBUG: check_full_rows\n");

  for(int y = 0; y < s->grid_size.y; y++) {
    int ok = 1;
    for(int x = 0; x < s->grid_size.x; x++) {
      if(!get_tile(s, (vec2) { x, y })) {
        ok = 0;
        break;
      }
    }

    if(!ok)
      continue;

    s->eliminated_rows++;
    eliminate_row(s, y);
  }
}

int update(game_state * const s, int * const redraw) {
  s->frame_number++;
  
  *redraw = 0;
  
  if(should_tick(s)) {
    tick(s);
    *redraw = 1;
  }

  check_full_rows(s);

  // TODO:
  // * handle inputs
  // * check frame_number to move tetromino down
  //   -> handle collision with dead tiles & bounds
  //      -> freezing tiles
  //   -> check for full rows & eliminate
  
  return 1;
}

///// DRAWING /////

/**
 * \brief
 * Draws a tile at grid-local position `pos` with the given color.
 */
void draw_tile(game_state * const s, vec2 pos, bgr color) {
  // convert grid-local position to screen position
  pos = (vec2) { pos.x * s->tile_size.x, pos.y * s->tile_size.y };
  // upgrade to rectangle
  rect r = { pos.x, pos.y, s->tile_size.x, s->tile_size.y };
  // fill the rectangle on screen
  fill_rect(
    s->lfb,
    rect_add(r, s->grid_origin),
    color);
}

void draw_tetromino(game_state * const s) {
  Print(L"DEBUG: drawing tetromino\n");
  for(UINT8 i = 0; i < TETROMINO_GRID_LENGTH; i++) {
    if(!s->current_tetromino.template->data[i]) {
      Print(L"DEBUG: skipping component %d\n", i);
      continue;
    }
    else
      Print(L"DEBUG: drawing component %d\n", i);

    vec2 p = tetro_index_to_tetro_local(i);

    Print(
      L"DEBUG: converted index %d to local position (%d, %d)\n",
      i,
      p.x,
      p.y);

    vec2 q = tetro_local_to_grid_local(&s->current_tetromino, p);

    Print(
      L"DEBUG: converted local position (%d, %d) to grid position (%d, %d)\n",
      p.x,
      p.y,
      q.x,
      q.y);

    draw_tile(s, q, TETRO_COLOR);
  }
}

void draw_dead_tiles(game_state * const s) {
  for(int i = 0; i < s->grid_size.x * s->grid_size.y; i++) {
    if(!s->grid[i])
      continue;

    vec2 p = grid_index_to_grid_local(i);
    draw_tile(s, p, DEAD_COLOR);
  }
}

void draw(game_state * const s) {
  // clear the screen buffer to black
  screen_buffer_clear(s->lfb, BLACK);

  // do all draws to the buffer

  // draw_tile(s, (vec2) { 0, 0 }, RED); // DEBUG
  draw_tetromino(s);
  draw_dead_tiles(s);

  // copy the buffer to the vram
  screen_buffer_copy(s->lfb);
}

///// MAIN LOOP /////

int game(game_state * const s) {
  int ok = 1, redraw = 0;
  while(ok) {
    ok = update(s, &redraw);
    if(redraw)
      draw(s);
    await_timer(&s->timer);
  }

  return 1;
}

