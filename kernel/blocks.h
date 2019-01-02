#ifndef BLOCKS_H
#define BLOCKS_H

/**
 * Definitions of tetris blocks as arrays of uint8_t.
 */

// because the grid is 2 rows 4 columns, there are 8 entries.
#define GRID_LENGTH 8

/**
 * \brief
 * A piece template is an array of bytes representing a 5x5 grid in
 * which the piece is represented.
 */
typedef struct tetromino_template {
  unsigned char data[GRID_LENGTH];
} tetromino_template;

#define TETROMINO_COUNT 7

// the available tetrominoes
tetromino_template const tetro_i, tetro_o, tetro_t, tetro_s, tetro_z, tetro_j, tetro_l;

// an array of pointers to the tetrominoes.
tetromino_template const * const tetrominos[TETROMINO_COUNT];

#endif
