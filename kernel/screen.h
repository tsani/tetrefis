#ifndef SCREEN_H
#define SCREEN_H

#include <efi.h>
#include <efilib.h>

#include "basic_types.h"

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

/**
 * \brief
 * Some predetermined colors.
 */
const bgr WHITE, RED, BLUE, GREEN, BLACK;

/**
 * \brief
 * A more compact way of creating a BGR color.
 */
#define BGR(b, g, r) (bgr) { .blue = (b), .green = (g), .red = (r), .unused = 0 }

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

/**
 * \brief
 * Clears the screen with a given color.
 */
void lfb_clear(LFB * const lfb, bgr color);

#endif
