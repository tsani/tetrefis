#ifndef CONFIG_H
#define CONFIG_H

// Turns on mock graphics mode, which disables the use of the GOP
// and instead performs all graphics operations on an internal static
// buffer. Consequently, the console is still visible and so are all
// print statements.
#define MOCK_LFB 0

// The initial difficulty level. Higher numbers are easier.
#define INITIAL_TICK_PERIOD 90

// The dimensions of the playfield.
#define GRID_WIDTH 10
#define GRID_HEIGHT 20

// Every N rows, the level goes up
#define LEVEL_BOUNDARY 10

// The scoring parameters.
typedef enum score_delta {
  SCORE_1 = 100,
  SCORE_2 = 250,
  SCORE_3 = 500,
  SCORE_4 = 1000
} score_delta;

#endif
