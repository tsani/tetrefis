#ifndef BLOCKS_H
#define BLOCKS_H

#include "basic_types.h"

/**
 * Definitions of tetrominos as arrays of uint8_t.
 * Each tetromino has a _pivot_, around which it rotates.
 */

#define TETROMINO_WIDTH 4
#define TETROMINO_HEIGHT 2

// because the grid is 2 rows 4 columns, there are 8 entries.
#define TETROMINO_GRID_LENGTH (TETROMINO_WIDTH * TETROMINO_HEIGHT) 

/**
 * \brief
 * A tetromino template is an array of bytes representing
 * TETROMINO_HEIGHT by TETROMINO_WIDTH grid in which the tetromino is
 * represented.
 */
typedef struct tetromino_template {
  unsigned char data[TETROMINO_GRID_LENGTH];
} tetromino_template;

#define TETROMINO_COUNT 7

// the available tetrominoes
extern tetromino_template const tetro_i, tetro_o, tetro_t, tetro_s, tetro_z, tetro_j, tetro_l;

// an array of pointers to the tetrominoes.
extern tetromino_template const * const TETROMINOES[TETROMINO_COUNT];

/**
 * \brief
 * A tetromino.
 *
 * This is a tetromino_template equipped with a position and rotation.
 */
typedef struct tetromino {
  /**
   * \brief
   * The basic template of the tetromino.
   *
   * Should be from TETROMINOS.
   */
  tetromino_template const * template;

  /**
   * \brief
   * The position of the tetromino's pivot in world-space.
   */
  vec2 position;

  /**
   * \brief
   * The rotation of the tetromino.
   */
  rotation rotation;
} tetromino;

/**
 * \brief
 * Converts a local position in a tetromino into a global position.
 *
 * q = tetro_local_to_global(t, p) tells us that q is the position in
 * world-space where the block at location p in the tetromino is.
 *
 * Note that location p is interpreted relative to the tetromino
 * pivot.
 *
 * This is done by rotating the tetro local position according to the
 * rotation of the tetromino and then adding the tetromino position.
 */
vec2 tetro_local_to_grid_local(tetromino const * const t, vec2 pos);

/**
 * \brief
 * Converts an array index into a two-dimensional vector representing
 * the position of that array element in the local coordinate system
 * of the tetromino, whose origin is its pivot.
 */
vec2 tetro_index_to_tetro_local(UINT8 index);

#endif
