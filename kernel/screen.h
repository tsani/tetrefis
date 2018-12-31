#ifndef SCREEN_H
#define SCREEN_H

#include <efi.h>
#include <efilib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/**
 * \brief
 * Represents a color in the blue-green-red-reserved format we demand
 * of the video driver.
 */
typedef struct bgr {
  UINT8 blue;
  UINT8 green;
  UINT8 red;
  UINT8 unused;
} bgr;

const bgr WHITE, RED, BLUE, GREEN, BLACK;

/**
 * \brief
 * Represents a rectangle by its top-left coordinate and its size.
 */
typedef struct rect {
  UINT32 x;
  UINT32 y;
  UINT32 w;
  UINT32 h;
} rect;

/**
 * \brief
 * A two-dimensional integer vector.
 */
typedef struct vec2 {
  UINT32 x;
  UINT32 y;
} vec2;

/**
 * \brief
 * The linear framebuffer and its associated metadata.
 */
typedef struct LFB {
  bgr * const pixels;
  UINTN const width, height, pixels_per_scanline;
} LFB;

#define SET_PIXEL(lfb, x, y, color) (lfb)->pixels[(x) + (lfb)->width * (y)] = (color)

void fill_rect(LFB * const lfb, rect rect, bgr color);

#endif
