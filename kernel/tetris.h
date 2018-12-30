#ifndef TETRIS_H
#define TETRIS_H

#define GRID_W 10
#define GRID_H 20

#include "screen.h"
#include "rng.h"

typedef UINT8 tile;

#define GRID_SIZE (GRID_W * GRID_H * sizeof(tile))

tile const EMPTY = 0;

typedef struct game_state {
  LFB * const lfb;
  RNG * const rng;
  tile grid[GRID_H * GRID_W];
} game_state;

game_state make_initial_state(LFB * const lfb, RNG * const rng) {
  game_state s = {
    .lfb = lfb,
    .rng = rng,
  };
  
  for(int i = 0; i < GRID_W * GRID_H; i++) {
    s.grid[i] = EMPTY;
  }

  return s;
}

/**
 * \brief
 * Retrieves a reference to a particular tile, given its coordinats.
 */
tile * ref_tile(game_state * const s, vec2 p);

EFI_STATUS game(game_state * const s);

#endif
