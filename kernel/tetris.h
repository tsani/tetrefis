#ifndef TETRIS_H
#define TETRIS_H

#define GRID_W 10
#define GRID_H 20

#include "screen.h"
#include "rng.h"
#include "time.h"

typedef UINT8 tile;

// the size in bytes of the grid
#define GRID_SIZE (GRID_W * GRID_H * sizeof(tile))

tile const EMPTY;

typedef struct game_state {
  LFB * const lfb;
  RNG * const rng;
  timer timer;
  tile grid[GRID_H * GRID_W];
} game_state;

game_state
make_initial_state(int * const ok, LFB * const lfb, RNG * const rng);

/**
 * \brief
 * Retrieves a reference to a particular tile, given its coordinats.
 */
tile *
ref_tile(game_state * const s, vec2 p);

int
game(game_state * const s);

#endif
