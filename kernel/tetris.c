#include "tetris.h"

///// DEFINITIONS /////

// milliseconds, roughly
int const FRAME_TIME = 10; 

// color of dead tetrominos in the grid
bgr const DEAD_COLOR = BGR(128, 128, 128);

// color of the player's tetromino
bgr const TETRO_COLOR = BGR(192, 96, 96);

// color of the boundary around the playfield
bgr const BOUNDARY_COLOR = BGR(192, 192, 192);

// dimensions of the tiles
INT32 const TILE_WIDTH = 16, TILE_HEIGHT = 16;

// empty tile and nonempty tile
tile const EMPTY = 0, NONEMPTY = 1;

///// LOGIC /////

UINT32 tick_period(game_state const * const s) {
  return s->level >= LEVEL_MAX ? 1 : s->levels[s->level];
}

/**
 * \brief
 * Converts an index into the grid array into a grid-local tile
 * coordinate.
 *
 * This is the inverse of `tile_index`.
 */
vec2 grid_index_to_grid_local(vec2 grid_size, int i) {
  return (vec2) { .x = i % grid_size.x, .y = i / grid_size.x };
}

/**
 * \brief
 * Converts a grid-local tile coordinate into a grid array index.
 *
 * This is the inverse of `grid_index_to_grid_local`.
 */
int tile_index(vec2 grid_size, vec2 p) {
  return p.x + p.y * grid_size.x;
}

/**
 * \brief
 * Reads tile data from the grid at the given position.
 */
tile get_tile(game_state const * const s, vec2 p) {
  return s->grid[tile_index(s->grid_size, p)];
}

/**
 * \brief
 * Obtains a reference to a tile in the grid at a given position.
 */
tile * ref_tile(game_state * const s, vec2 p) {
  return &s->grid[tile_index(s->grid_size, p)];
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
make_initial_state(
  int * const ok,
  LFB * const lfb,
  RNG * const rng,
  input_manager_t * const input_manager) {
  //
  int _ok;
  
  game_state s = {
    .lfb = lfb,
    .rng = rng,
    .timer = make_timer(&_ok, FRAME_TIME),
    .next_tetromino = &tetro_l,
    .frame_number = 0,
    .tile_size = (vec2) { .x = TILE_WIDTH, .y = TILE_HEIGHT },
    .grid_size = (vec2) { .x = GRID_WIDTH, .y = GRID_HEIGHT },
    // center the grid
    .grid_origin = (vec2) {
      .x = lfb->width / 2 - GRID_WIDTH * TILE_WIDTH / 2,
      .y = lfb->height / 2 - GRID_HEIGHT * TILE_HEIGHT / 2
    },
    .last_tick = 0,
    .eliminated_rows = 0,
    .input_manager = input_manager,
    .score_table = {
      0, // no rows cleared -> no points added
      SCORE_1, // see config.h
      SCORE_2,
      SCORE_3,
      SCORE_4
    },
    .level = 0,
    .levels = {
      90, 80, 70, 60, 50,
      45, 40, 35, 30, 25,
      20, 18, 16, 14, 12,
      10,  8,  5,  3,  2
    }
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

  // skip the first two (bogus / default) values for the tetrominoes
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
    *ref_tile(s, q) = NONEMPTY;
  }
}

/**
 * \brief
 * Freezes the current tetromino, spawns a new one, and checks for
 * gameover.
 *
 * \returns
 * - `0` if the game is over.
 * - `1` if the game continues.
 */
int freeze_and_next_tetromino(game_state * const s) {
  freeze_tetromino(s);
  
  // if right after spawning the next tetromino, it is invalid, then
  // we've hit gameover
  next_tetromino(s);
  return is_tetromino_valid(s);
}

/**
 * \brief
 * Moves the tetromino down, checking for collisions and freezing it
 * if necessary.
 *
 * This function also detects the game over condition, and returns
 * false if the game is over.
 */
int tick(game_state * const s) {
  Print(L"DEBUG: tick!\n");
  s->current_tetromino.position.y++;
  if(!is_tetromino_valid(s)) {
    Print(L"DEBUG: tetromino invalid; freezing and getting next\n");
    s->current_tetromino.position.y--;
    if(!freeze_and_next_tetromino(s))
      return 0;
  }

  s->last_tick = s->frame_number;
  return 1;
}

int should_tick(game_state * const s) {
  return s->frame_number - s->last_tick >= tick_period(s);
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

void update_level(game_state * const s) {
  s->level = s->eliminated_rows / LEVEL_BOUNDARY;
  if(s->level >= LEVEL_MAX)
    s->level = LEVEL_MAX;
}

void check_full_rows(game_state * const s) {
  Print(L"DEBUG: check_full_rows\n");

  int eliminated_rows = 0;

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

    eliminated_rows++;
    eliminate_row(s, y);
  }

  s->eliminated_rows += eliminated_rows;
  s->score += s->score_table[eliminated_rows];
}

int on_move_left(game_state * const s) {
  s->current_tetromino.position.x--;
  if(!is_tetromino_valid(s))
    s->current_tetromino.position.x++;
  return 1;
}

int on_move_right(game_state * const s) {
  s->current_tetromino.position.x++;
  if(!is_tetromino_valid(s))
    s->current_tetromino.position.x--;
  return 1;
}

int on_rotate_ccw(game_state * const s) {
  rotation r = s->current_tetromino.rotation;
  s->current_tetromino.rotation = rot_inc(s->current_tetromino.rotation);
  if(!is_tetromino_valid(s))
    s->current_tetromino.rotation = r;
  return 1;
}

int on_rotate_cw(game_state * const s) {
  rotation r = s->current_tetromino.rotation;
  s->current_tetromino.rotation = rot_dec(s->current_tetromino.rotation);
  if(!is_tetromino_valid(s))
    s->current_tetromino.rotation = r;
  return 1;
}

int on_fall(game_state * const s) {
  while(is_tetromino_valid(s)) {
    s->current_tetromino.position.y++;
  }
  s->current_tetromino.position.y--;
  if(!freeze_and_next_tetromino(s))
    return 0;
  check_full_rows(s);
  return 1;
}

int on_quit(game_state * const s) {
  return 0;
}

int on_unknown(game_state * const s) {
  return 1;
}

/**
 * \brief
 * Type of a function that handles an input key.
 *
 * The returned integer indicates whether the game continues:
 * - `0` indicates the game is over.
 * - `1` indicates the game continues.
 */
typedef int (*input_handler)(game_state * const s);

/**
 * \brief
 * Table of function pointers that handle the input keys, precisely in
 * the enum order of `INPUT_KEY`, so we can use the enum values as
 * indices.
 */
input_handler input_handlers[INPUT_KEY_MAX] = {
  // conveniently, tick has the right type for an input handler,
  // so we use it directly to handle the down input
  tick, 
  on_move_left,
  on_move_right,
  on_rotate_ccw,
  on_rotate_cw,
  on_fall,
  on_quit,
  on_unknown
};

int handle_input(game_state * const s, int * const redraw) {
  INPUT_KEY key;
  READ_INPUT_KEY_STATUS status;
  // keep processing inputs until we run out or hit an error
  // for each input, invoke its appropriate handler and eager-exit if
  // it indicates game over.
  while(INPUT_KEY_SUCCESS == (status = read_input_key(s->input_manager, &key))) {
    Print(L"DEBUG: handling input %d\n", key);
    if(!input_handlers[key](s)) {
      Print(L"DEBUG: handle_input gameover detected\n");
      return 0;
    }
    else
      *redraw = 1;
  }

  if(status == INPUT_KEY_ERROR) {
    Print(L"ERROR: failed to read input\n");
    return 0;
  }

  return 1;
}

int update(game_state * const s, int * const redraw) {
  s->frame_number++;

  if(!handle_input(s, redraw))
    return 0;
  
  if(should_tick(s)) {
    if(!tick(s))
      return 0;

    check_full_rows(s);
    *redraw = 1;
  }
  
  update_level(s);

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

void draw_boundary(game_state * const s) {
  for(int y = 0; y < s->grid_size.y; y++) {
    draw_tile(s, (vec2) { .x = -1, .y = y }, BOUNDARY_COLOR);
    draw_tile(s, (vec2) { .x = s->grid_size.x, .y = y }, BOUNDARY_COLOR);
  }

  for(int x = -1; x < s->grid_size.x + 1; x++) {
    draw_tile(s, (vec2) { .x = x, .y = s->grid_size.y }, BOUNDARY_COLOR);
  }
}

void draw_tetromino(game_state * const s, tetromino const * const t) {
  Print(L"DEBUG: drawing tetromino\n");
  for(UINT8 i = 0; i < TETROMINO_GRID_LENGTH; i++) {
    if(!t->template->data[i]) {
      // Print(L"DEBUG: skipping component %d\n", i);
      continue;
    }
    else {
      // Print(L"DEBUG: drawing component %d\n", i);
    }

    vec2 p = tetro_index_to_tetro_local(i);

    // Print(
    //   L"DEBUG: converted index %d to local position (%d, %d)\n",
    //   i,
    //   p.x,
    //   p.y);

    vec2 q = tetro_local_to_grid_local(t, p);

    // Print(
    //   L"DEBUG: converted local position (%d, %d) to grid position (%d, %d)\n",
    //   p.x,
    //   p.y,
    //   q.x,
    //   q.y);

    draw_tile(s, q, TETRO_COLOR);
  }
}

void draw_dead_tiles(game_state * const s) {
  for(int i = 0; i < s->grid_size.x * s->grid_size.y; i++) {
    if(s->grid[i] == EMPTY)
      continue;
    else {
      // Print(L"DEBUG: drawing dead tile at index %d\n", i);
    }

    vec2 p = grid_index_to_grid_local(s->grid_size, i);
    // Print(L"DEBUG: %d = (%d, %d)\n", i, p.x, p.y);
    draw_tile(s, p, DEAD_COLOR);
  }
}

void draw(game_state * const s) {
  // used to draw the next tetromino
  static tetromino t = {
    .template = NULL,
    .position = (vec2) { .x = 0, .y = 0 },
    .rotation = ZERO_ROTATION
  };

  // clear the screen buffer to black
  screen_buffer_clear(s->lfb, BLACK);

  // do all draws to the buffer

  draw_tetromino(s, &s->current_tetromino);

  t.position.x = s->grid_size.x + 4;
  t.template = s->next_tetromino;
  draw_tetromino(s, &t);

  draw_dead_tiles(s);
  draw_boundary(s);

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

