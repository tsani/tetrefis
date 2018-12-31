#include "tetris.h"

game_state
make_initial_state(int * const ok, LFB * const lfb, RNG * const rng) {
  int _ok;
  
  game_state s = {
    .lfb = lfb,
    .rng = rng,
    .timer = make_timer(&_ok, 15)
  };

  if(!_ok) {
    *ok = _ok;
    return s;
  }
  
  for(int i = 0; i < GRID_W * GRID_H; i++) {
    s.grid[i] = EMPTY;
  }

  *ok = 1;

  return s;
}

tile * ref_tile(game_state * const s, vec2 p) {
  return &s->grid[p.x + p.y * GRID_W];
}

int game(game_state * const s) {


  UINT32 i = 0;
  do {
    await_timer(&s->timer);
    s->lfb->pixels[i] = WHITE;
  } while(++i);

  return 1;
}
