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
    0, 1, 0, 0,
    1, 1, 1, 0
  }
};

tetromino_template const tetro_s = {
  {
    0, 0, 1, 1,
    0, 1, 1, 0
  }
};

tetromino_template const tetro_z = {
  {
    0, 1, 1, 0,
    0, 0, 1, 1
  }
};

tetromino_template const tetro_j = {
  {
    0, 1, 0, 0,
    0, 1, 1, 1
  }
};

tetromino_template const tetro_l = {
  {
    0, 0, 0, 1,
    0, 1, 1, 1
  }
};

tetromino_template const * const tetrominos[TETROMINO_COUNT] = {
  &tetro_i,
  &tetro_o,
  &tetro_t,
  &tetro_s,
  &tetro_z,
  &tetro_j,
  &tetro_l
};
