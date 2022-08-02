#ifndef TEXT_H
#define TEXT_H

#include <efi.h>

#include "basic_types.h"
#include "screen.h"

///////////////////////////
// bitmap text rendering //
///////////////////////////

/**
 * \brief
 * A bitmap text character.
 * Defines a font element.
 */
typedef struct bt_char {
  /**
   * Index of the row used for vertical character alignment.
   */
  int baseline;
  /**
   * \brief
   * The width of the data array.
   */
  int width;
  /**
   * \brief
   * The height of the data array.
   */
  int height;
  /**
   * \brief
   * The character data as a dense matrix.
   *
   * True values are drawn and false values are skipped.
   * These values are called _character elements_.
   */
  UINT8 data[];
} bt_char;

/**
 * \brief
 * Reads the character element at the given position in the character.
 */
UINT8 get_char_el(bt_char const * const c, vec2 p);

/**
 * \brief
 * A dense mapping of ASCII code points to bt_char structures.
 */
typedef struct bt_font {
  bt_char const * const characters[128];
} bt_font;

extern bt_font const default_font;

/**
 * \brief
 * Information used to render a string.
 */
typedef struct bt_renderer_info {
  /**
   * \brief
   * The color to use to draw character elements.
   */
  bgr const color;
  /**
   * \brief
   * The font to use to draw the characters.
   */
  bt_font const * const font;
  /**
   * \brief
   * The size in pixels of each character element.
   */
  UINT8 const text_scale;
  /**
   * \brief
   * The number of character elements to place between characters.
   */
  UINT8 const char_skip;
} bt_renderer_info;

/**
 * \brief
 * Renders a string to the screen, left-aligned to the given position.
 */
void
bt_render_string(
  LFB * const dest,
  bt_renderer_info const * const renderer_info,
  vec2 const origin,
  char const * const str,
  UINT32 length);

/**
 * \brief
 * Renders a string to the screen, centered at the given position.
 *
 * This isn't particularly efficient since a pass is done over the
 * string to determine its width before offsetting it.
 */
void
bt_render_string_centered(
  LFB * const dest,
  bt_renderer_info const * const renderer_info,
  vec2 const origin,
  char const * const str,
  UINT32 length);

/**
 * \brief
 * Measures how wide a string would be when rendered on screen.
 */
UINT32
measure_string_width(
  bt_renderer_info const * const renderer_info,
  char const * const str,
  UINT32 length);

/**
 * \brief
 * Converts the number to a string representation.
 *
 * The result is written *right-aligned* to the end of the destination
 * string.
 * If the string is not long enough (according to length) to represent
 * the number, then 0 is returned. Otherwise 1 is returned.
 */
int
uint32_to_str(
  UINT32 num,
  char * const dest,
  UINT32 length);

#endif
