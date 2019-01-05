#include "tetris.h"

///// DEFINITIONS /////

int const FRAME_TIME = 0;
bgr const DEAD_COLOR = BGR(128, 128, 128);
bgr const TETRO_COLOR = BGR(192, 96, 96);

UINT32 const TILE_WIDTH = 16, TILE_HEIGHT = 16;

///// LOGIC /////

/**
 * \brief
 * Converts a grid-local tile coordinate into a grid array index.
 */
int tile_index(game_state * const s, vec2 p) {
  return p.x + p.y * s->grid_size.x;
}

tile * ref_tile(game_state * const s, vec2 p) {
  return &s->grid[tile_index(s, p)];
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
    }
  };

  if(!_ok) {
    *ok = _ok;
    return s;
  }
  
  for(int i = 0; i < s.grid_size.x * s.grid_size.y; i++) {
    s.grid[i] = EMPTY;
  }

  *ok = 1;

  return s;
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

int update(game_state * const s, int * const redraw) {
  static int q = 1;
  *redraw = q;
  q = 0;
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
  rect r = { pos.x, pos.y, 16, s->tile_size.y };
  fill_rect(
    s->lfb,
    rect_add(r, s->grid_origin),
    color);
}

void draw_tetromino(game_state * const s) {
  for(UINT8 i = 0; i < TETROMINO_GRID_LENGTH; i++) {
    if(!s->current_tetromino.template->data[i])
      continue;

    vec2 p = tetro_index_to_tetro_local(i);
    vec2 q = tetro_local_to_grid_local(&s->current_tetromino, p);

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
  lfb_clear(s->lfb, BLACK);
  draw_tile(s, (vec2) { 0, 0 }, RED); // DEBUG
  // draw_tetromino(s);
  // draw_dead_tiles(s);
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

