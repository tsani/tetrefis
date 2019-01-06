#ifndef TETRIS_H
#define TETRIS_H

#include "screen.h"
#include "rng.h"
#include "time.h"
#include "blocks.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define INITIAL_TICK_PERIOD 90

///// TYPES & CONSTANTS /////

typedef UINT8 tile;

typedef struct game_state {
  /**
   * \brief
   * The framebuffer to draw the game in.
   */
  LFB * const lfb;

  /**
   * \brief
   * The random number generator used to get new tetrominos.
   */
  RNG * const rng;

  /**
   * \brief
   * The timer used to pause between frames.
   */
  timer timer;

  /**
   * \brief
   * A reference to the next tetromino that the player will get.
   */
  tetromino_template const * next_tetromino;

  /**
   * \brief
   * The tetromino that the player is controlling.
   */
  tetromino current_tetromino;

  /**
   * \brief
   * The grid of tiles that are frozen.
   */
  tile grid[GRID_HEIGHT * GRID_WIDTH];

  /**
   * \brief
   * Number of frames that have elapsed.
   */
  UINT32 frame_number;

  /**
   * \brief
   * The absolute position in pixels where the grid begins on screen.
   */
  vec2 const grid_origin;

  /**
   * \brief
   * The size of the grid in tiles.
   */
  vec2 const grid_size;

  /**
   * \brief
   * The size of a tile in pixels.
   */
  vec2 const tile_size;

  /**
   * \brief
   * Number of frames that elapse between ticks.
   *
   * The tick is when the tetromino falls down one block.
   */
  UINT8 tick_period;

  /**
   * \brief
   * The frame number when the last tick occurred.
   */
  UINT32 last_tick;

  /**
   * \brief
   * The number of rows eliminated by the player.
   */
  UINT32 eliminated_rows;
} game_state;

/**
 * \brief
 * Indicates that the grid tile is empty.
 */
tile const EMPTY;

/**
 * \brief
 * Indicates that the grid tile is nonempty.
 */
tile const DEAD;

/**
 * \brief
 * The color for "dead" tiles in the grid.
 */
bgr const DEAD_COLOR;

/**
 * \brief
 * The color for components of active tetrominoes.
 */
bgr const TETRO_COLOR;

///// FUNCTIONS /////

/**
 * \brief
 * Constructs an initial state for the game.
 *
 * Returns whether the initialization succeeded in the out-parameter
 * `ok`.
 */
game_state
make_initial_state(int * const ok, LFB * const lfb, RNG * const rng);

/**
 * \brief
 * Converts an index into the tile grid into a 2d vector representing
 * that tile's local position in the grid.
 */
vec2 grid_index_to_grid_local(int i);

/**
 * \brief
 * Retrieves a reference to a particular tile, given its coordinats.
 */
tile *
ref_tile(game_state * const s, vec2 p);

/**
 * \brief
 * Runs the game loop.
 */
int
game(game_state * const s);

#endif
