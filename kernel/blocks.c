#include "blocks.h"

tetromino_template const tetro_i = {
  {
    1, 1, 1, 1,
    0, 0, 0, 0
  }
};

tetromino_template const tetro_o = {
  {
    0, 1, 1, 0,
    0, 1, 1, 0
  }
};

tetromino_template const tetro_t = {
  {
    1, 1, 1, 0,
    0, 1, 0, 0
  }
};

tetromino_template const tetro_s = {
  {
    0, 1, 1, 0,
    1, 1, 0, 0
  }
};

tetromino_template const tetro_z = {
  {
    1, 1, 0, 0,
    0, 1, 1, 0
  }
};

tetromino_template const tetro_j = {
  {
    1, 1, 1, 0,
    1, 0, 0, 0
  }
};

tetromino_template const tetro_l = {
  {
    1, 1, 1, 0,
    0, 0, 1, 0
  }
};

tetromino_template const * const TETROMINOES[TETROMINO_COUNT] = {
  &tetro_i,
  &tetro_o,
  &tetro_t,
  &tetro_s,
  &tetro_z,
  &tetro_j,
  &tetro_l
};

vec2 const PIVOT_OFFSET = { .x = 1, .y = 0 };

vec2 tetro_index_to_tetro_local(UINT8 index) {
  // p is the column-row representation (origin in top-left corner)
  vec2 p = { index % TETROMINO_WIDTH, index / TETROMINO_WIDTH };
  // convert to pivot at origin
  return vec2_add(p, vec2_flip(PIVOT_OFFSET));
}

vec2 tetro_local_to_grid_local(tetromino const * const t, vec2 pos) {
  return vec2_add(t->position, apply_rotation(t->rotation, pos));
}
