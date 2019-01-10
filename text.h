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

// bt_char const bt_char_a;
// bt_char const bt_char_b;
// bt_char const bt_char_c;
// bt_char const bt_char_d;
// bt_char const bt_char_e;
// bt_char const bt_char_f;
// bt_char const bt_char_g;
// bt_char const bt_char_h;
// bt_char const bt_char_i;
// bt_char const bt_char_j;
// bt_char const bt_char_k;
// bt_char const bt_char_l;
// bt_char const bt_char_m;
// bt_char const bt_char_n;
// bt_char const bt_char_o;
// bt_char const bt_char_p;
// bt_char const bt_char_q;
// bt_char const bt_char_r;
// bt_char const bt_char_s;
// bt_char const bt_char_t;
// bt_char const bt_char_u;
// bt_char const bt_char_v;
// bt_char const bt_char_w;
// bt_char const bt_char_x;
// bt_char const bt_char_y;
// bt_char const bt_char_z;
// bt_char const bt_char_0;
// bt_char const bt_char_1;
// bt_char const bt_char_2;
// bt_char const bt_char_3;
// bt_char const bt_char_4;
// bt_char const bt_char_5;
// bt_char const bt_char_6;
// bt_char const bt_char_7;
// bt_char const bt_char_8;
// bt_char const bt_char_9;
// bt_char const bt_char_sp;

/**
 * \brief
 * A dense mapping of ASCII code points to bt_char structures.
 */
typedef struct bt_font {
  bt_char const * const characters[128];
} bt_font;

bt_font const default_font;

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
