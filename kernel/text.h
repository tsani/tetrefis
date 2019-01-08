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

bt_char const bt_char_a;
bt_char const bt_char_b;
bt_char const bt_char_c;
bt_char const bt_char_d;
bt_char const bt_char_e;
bt_char const bt_char_f;
bt_char const bt_char_g;
bt_char const bt_char_h;
bt_char const bt_char_i;
bt_char const bt_char_j;
bt_char const bt_char_k;
bt_char const bt_char_l;
bt_char const bt_char_m;
bt_char const bt_char_n;
bt_char const bt_char_o;
bt_char const bt_char_p;
bt_char const bt_char_q;
bt_char const bt_char_r;
bt_char const bt_char_s;
bt_char const bt_char_t;
bt_char const bt_char_u;
bt_char const bt_char_v;
bt_char const bt_char_w;
bt_char const bt_char_x;
bt_char const bt_char_y;
bt_char const bt_char_z;
bt_char const bt_char_0;
bt_char const bt_char_1;
bt_char const bt_char_2;
bt_char const bt_char_3;
bt_char const bt_char_4;
bt_char const bt_char_5;
bt_char const bt_char_6;
bt_char const bt_char_7;
bt_char const bt_char_8;
bt_char const bt_char_9;
bt_char const bt_char_sp;

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
   * Where to begin drawing the first character.
   */
  vec2 const origin;
  /**
   * \brief
   * The size in pixels of each character element.
   */
  UINT8 const text_scale;
  /**
   * \brief
   * The color to use to draw character elements.
   */
  bgr const color;
  /**
   * \brief
   * The buffer to draw the text into.
   */
  LFB * const dest;
  /**
   * \brief
   * The number of character elements to place between characters.
   */
  UINT8 const char_skip;
  /**
   * \brief
   * The font to use to draw the characters.
   */
  bt_font const * const font;
} bt_renderer_info;

/**
 * \brief
 * Renders a string to the screen.
 */
void
bt_render_string(
  bt_renderer_info * const renderer_info,
  char const * const str);

#endif
