#ifndef TETRIS_H
#define TETRIS_H

#include "screen.h"
#include "rng.h"
#include "time.h"
#include "blocks.h"
#include "input.h"
#include "text.h"

///// TYPES & CONSTANTS /////

#define LEVEL_MAX 20

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
   * Service to read keystrokes.
   */
  input_manager_t * const input_manager;

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
   * The frame number when the last tick occurred.
   */
  UINT32 last_tick;

  /**
   * \brief
   * The number of rows eliminated by the player.
   */
  UINT32 eliminated_rows;

  /**
   * \brief
   * Player score.
   */
  UINT32 score;

  /**
   * \brief
   * Score values to add for different numbers of lines cleared.
   */
  score_delta const score_table[5];

  /**
   * \brief
   * The current level.
   * This is an index into the `levels` array.
   */
  UINT8 level;

  /**
   * \brief
   * This is all the difficulty levels, expressed as tick periods.
   */
  UINT8 const levels[LEVEL_MAX];

  /**
   * \brief
   * Settings for rendering text.
   */
  bt_renderer_info const renderer_info;
} game_state;

/**
 * \brief
 * Indicates that the grid tile is empty.
 */
tile const EMPTY, NONEMPTY;

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
 * `ok`. The return value is undefined if `*ok` isn't true.
 */
game_state
make_initial_state(
  int * const ok,
  LFB * const lfb,
  RNG * const rng,
  input_manager_t * const input_manager);

/**
 * \brief
 * Runs the game loop.
 */
int
game(game_state * const s);

#endif
