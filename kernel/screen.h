#ifndef SCREEN_H
#define SCREEN_H

#include <efi.h>
#include <efilib.h>

#include "config.h"
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

typedef struct mock_vram_t {
  bgr data[SCREEN_WIDTH * SCREEN_HEIGHT];
} mock_vram_t;

mock_vram_t SCREEN_BUFFER;

/**
 * \brief
 * The linear framebuffer and its associated metadata.
 */
typedef struct LFB {
  bgr * const pixels;
  bgr * const buffer;
  UINTN const width, height, pixels_per_scanline;
} LFB;

#define SET_PIXEL_INTERNAL(lfb, x, y, color, member) (lfb)->member[(x) + (lfb)->width * (y)] = (color)
#define SET_SCREEN_PIXEL(lfb, x, y, color) SET_PIXEL_INTERNAL(lfb, x, y, color, pixels) 
#define SET_BUFFER_PIXEL(lfb, x, y, color) SET_PIXEL_INTERNAL(lfb, x, y, color, buffer)

LFB load_lfb(EFI_STATUS * status);

/**
 * \brief
 * Fills a rectangle in the buffer.
 */
void fill_rect(LFB * const lfb, rect rect, bgr color);

/**
 * \brief
 * Copies the buffer into the real vram.
 */
void screen_buffer_copy(LFB * const lfb);

/**
 * \brief
 * Clears the screen with a given color.
 */
void screen_buffer_clear(LFB * const lfb, bgr color);

#endif
