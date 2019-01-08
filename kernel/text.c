#include "text.h"

UINT8
get_char_el(bt_char const * const c, vec2 p) {
  return c->data[p.x + c->width * p.y];
}

void
draw_character(
  LFB * const lfb,
  bt_char const * const c,
  vec2 top_left,
  bgr color) {
  //
  for(int i = 0; i < c->width; i++) {
    for(int j = 0; j < c->height; j++) {
      // skip empty character elements
      if(!get_char_el(c, (vec2) { i, j }))
        continue;

      SET_BUFFER_PIXEL(lfb, top_left.x + i, top_left.y + j, color);
    }
  }
}

void
bt_render_string_centered(
  LFB * const dest,
  bt_renderer_info const * const renderer_info,
  vec2 const origin,
  char const * const str,
  UINT32 length) {
  //
  INT32 w = measure_string_width(renderer_info, str, length);
  bt_render_string(
    dest,
    renderer_info,
    vec2_add(origin, (vec2) { -w/2, 0 }),
    str,
    length);
}

UINT32
measure_string_width(
  bt_renderer_info const * const renderer_info,
  char const * const str,
  UINT32 length) {
  //
  UINT32 w = 0;

  for(int i = 0; i < length; i++) {
    char c = str[i];
    bt_char const * const btc = renderer_info->font->characters[(int)c];
    w += btc->width;
    w ++;
  }

  if(w > 0)
    w--;
  return w;
}

void
bt_render_string(
  LFB * const dest,
  bt_renderer_info const * const renderer_info,
  vec2 const origin,
  char const * const str,
  UINT32 length) {
  // how far to the right have we travelled;
  UINT32 x0 = origin.x;

  Print(
    L"DEBUG: bt_draw_string '%s' at (%d, %d)\n",
    str,
    origin.x,
    origin.y);

  for(int i = 0; i < length; i++) {
    char c = str[i]; // widen char to int
    Print(L"DEBUG: drawing character '%c'\n", c);
    bt_char const * const btc = renderer_info->font->characters[(int)c];
    if(NULL == btc) {
      Print(L"ERROR: unknown character '%c'\n", c);
      continue;
    }

    Print(L"DEBUG: found bt_char for '%c'\n", c);
      
    // work out the position of the top-left corner of the character
    // the x coordinate is easy: it's x0
    // the y coordinate depends on the character's baseline
    draw_character(
      dest,
      btc,
      (vec2) { x0, origin.y - btc->baseline },
      renderer_info->color);

    x0 += btc->width + renderer_info->char_skip;
  }
}

//////////////////////
// DATA DEFINITIONS //
//////////////////////

// Prepare yourself for some SHIT.

#define X 1
#define n 0

bt_char const bt_char_a = {
  .width = 5,
  .height = 6,
  .baseline = 5,
  .data = {
    n, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, X
  }
};

bt_char const bt_char_b = {
  .width = 5,
  .height = 11,
  .baseline = 10,
  .data = {
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, n,
    X, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, n
  }
};

bt_char const bt_char_c = {
  .width = 4,
  .height = 6,
  .baseline = 5,
  .data = {
    n, X, X, X,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    n, X, X, X
  }
};

bt_char const bt_char_d = {
  .width = 5,
  .height = 11,
  .baseline = 10,
  .data = {
    n, n, n, n, X,
    n, n, n, n, X,
    n, n, n, n, X,
    n, n, n, n, X,
    n, n, n, n, X,
    n, X, X, X, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, n
  }
};

bt_char const bt_char_e = {
  .width = 5,
  .height = 6,
  .baseline = 5,
  .data = {
    n, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, X, X, n,
    X, n, n, n, n,
    n, X, X, X, X
  }
};

bt_char const bt_char_f = {
  .width = 4,
  .height = 11,
  .baseline = 10,
  .data = {
    n, X, X, X,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, X, X, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n
  }
};

bt_char const bt_char_g = {
  .width = 5,
  .height = 11,
  .baseline = 5,
  .data = {
    n, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, X,
    n, n, n, n, X,
    n, n, n, n, X,
    n, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, n
  }
};

bt_char const bt_char_h = {
  .width = 5,
  .height = 11,
  .baseline = 10,
  .data = {
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, n,
    X, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X
  }
};

bt_char const bt_char_i = {
  .width = 1,
  .height = 8,
  .baseline = 7,
  .data = {
    X,
    n,
    X,
    X,
    X,
    X,
    X,
    X
  }
};

bt_char const bt_char_j = {
  .width = 4,
  .height = 11,
  .baseline = 5,
  .data = {
    n, n, n, X,
    n, n, n, n,
    n, n, n, X,
    n, n, n, X,
    n, n, n, X,
    n, n, n, X,
    n, X, n, X,
    X, n, n, X,
    X, n, n, X,
    X, n, n, X,
    n, X, X, n
  }
};

bt_char const bt_char_k = {
  .width = 5,
  .height = 11,
  .baseline = 10,
  .data = {
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, X,
    X, n, n, X, n,
    X, n, X, n, n,
    X, X, X, n, n,
    X, n, X, n, n,
    X, n, n, X, n,
    X, n, n, X, n,
    X, n, n, n, X,
    X, n, n, n, X
  }
};

bt_char const bt_char_l = {
  .width = 1,
  .height = 11,
  .baseline = 10,
  .data = {
    X,
    X,
    X,
    X,
    X,
    X,
    X,
    X,
    X,
    X,
    X
  }
};

bt_char const bt_char_m = {
  .width = 7,
  .height = 6,
  .baseline = 5,
  .data = {
    X, X, n, X, X, n, n,
    X, n, X, X, n, X, n,
    X, n, n, X, n, n, X,
    X, n, n, X, n, n, X,
    X, n, n, X, n, n, X,
    X, n, n, n, n, n, X,
  }
};

bt_char const bt_char_n = {
  .width = 5,
  .height = 6,
  .baseline = 5,
  .data = {
    X, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X
  }
};

bt_char const bt_char_o = {
  .width = 5,
  .height = 6,
  .baseline = 5,
  .data = {
    n, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, n
  }
};

bt_char const bt_char_p = {
  .width = 5,
  .height = 11,
  .baseline = 5,
  .data = {
    n, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, X, X, X, n,
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, n,
    X, n, n, n, n
  }
};

bt_char const bt_char_q = {
  .width = 5,
  .height = 11,
  .baseline = 5,
  .data = {
    n, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, X,
    n, n, n, n, X,
    n, n, n, n, X,
    n, n, n, n, X,
    n, n, n, n, X,
    n, n, n, n, X
  }
};

bt_char const bt_char_r = {
  .width = 4,
  .height = 6,
  .baseline = 5,
  .data = {
    X, X, X, n,
    X, n, n, X,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n
  }
};

bt_char const bt_char_s = {
  .width = 4,
  .height = 6,
  .baseline = 5,
  .data = {
    n, X, X, n,
    X, n, n, X,
    X, n, n, n,
    n, X, X, n,
    n, n, n, X,
    X, X, X, n
  }
};

bt_char const bt_char_t = {
  .width = 4,
  .height = 11,
  .baseline = 10,
  .data = {
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, X, X, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    X, n, n, n,
    n, X, X, X
  }
};

bt_char const bt_char_u = {
  .width = 5,
  .height = 6,
  .baseline = 5,
  .data = {
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, X
  }
};

bt_char const bt_char_v = {
  .width = 4,
  .height = 6,
  .baseline = 5,
  .data = {
    X, n, n, X,
    X, n, n, X,
    X, n, n, X,
    n, X, n, X,
    n, X, n, X,
    n, n, X, n
  }
};

bt_char const bt_char_w = {
  .width = 7,
  .height = 6,
  .baseline = 5,
  .data = {
    X, n, n, X, n, n, X,
    X, n, n, X, n, n, X,
    X, n, n, X, n, n, X,
    n, X, n, X, n, n, X,
    n, X, n, X, X, n, X,
    n, n, X, n, n, X, n
  }
};

bt_char const bt_char_x = {
  .width = 5,
  .height = 6,
  .baseline = 5,
  .data = {
    X, n, n, n, X,
    n, X, n, X, n,
    n, n, X, n, n,
    n, n, X, n, n,
    n, X, n, X, n,
    X, n, n, n, X
  }
};

bt_char const bt_char_y = {
  .width = 5,
  .height = 11,
  .baseline = 5,
  .data = {
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, X,
    n, n, n, n, X,
    n, n, n, n, X,
    n, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, n
  }
};

bt_char const bt_char_z = {
  .width = 5,
  .height = 6,
  .baseline = 5,
  .data = {
    X, X, X, X, X,
    n, n, n, X, n,
    n, n, X, n, n,
    n, n, X, n, n,
    n, X, n, n, n,
    X, X, X, X, X
  }
};

bt_char const bt_char_0 = {
  .width = 5,
  .height = 11,
  .baseline = 10,
  .data = {
    n, X, X, X, n,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    X, n, n, n, X,
    n, X, X, X, n
  }
};

bt_char const bt_char_sp = {
  .width = 5,
  .height = 1,
  .baseline = 0,
  .data = {n, n, n, n, n}
};

#undef X
#undef n

bt_font const default_font = {
  .characters = {
    NULL, // NUL
    NULL, // SOH
    NULL, // STX 
    NULL, // ETX
    NULL, // EOT 
    NULL, // ENQ
    NULL, // ACK 
    NULL, // BEL
    NULL, // BS  
    NULL, // HT
    NULL, // LF  
    NULL, // VT
    NULL, // FF  
    NULL, // CR
    NULL, // SO  
    NULL, // SI
    NULL, // DLE 
    NULL, // DC1
    NULL, // DC2 
    NULL, // DC3
    NULL, // DC4 
    NULL, // NAK
    NULL, // SYN 
    NULL, // ETB
    NULL, // CAN 
    NULL, // EM
    NULL, // SUB 
    NULL, // ESC
    NULL, // FS  
    NULL, // GS
    NULL, // RS  
    NULL, // US
    &bt_char_sp, // SPA 
    NULL, // !
    NULL, // "   
    NULL, // #
    NULL, // $   
    NULL, // %
    NULL, // &   
    NULL, // '
    NULL, // (   
    NULL, // )
    NULL, // *   
    NULL, // +
    NULL, // ,   
    NULL, // -
    NULL, // .   
    NULL, // /
    &bt_char_0, // 0   
    NULL, // &bt_char_1, // 1
    NULL, // &bt_char_2, // 2   
    NULL, // &bt_char_3, // 3
    NULL, // &bt_char_4, // 4   
    NULL, // &bt_char_5, // 5
    NULL, // &bt_char_6, // 6   
    NULL, // &bt_char_7, // 7
    NULL, // &bt_char_8, // 8   
    NULL, // &bt_char_9, // 9
    NULL, // :   
    NULL, // ;
    NULL, // <   
    NULL, // =
    NULL, // >   
    NULL, // ?
    NULL, // @
    NULL, // A
    NULL, // B
    NULL, // C
    NULL, // D
    NULL, // E
    NULL, // F
    NULL, // G
    NULL, // H
    NULL, // I
    NULL, // J
    NULL, // K
    NULL, // L
    NULL, // M
    NULL, // N
    NULL, // O   
    NULL, // P   
    NULL, // Q   
    NULL, // R   
    NULL, // S   
    NULL, // T   
    NULL, // U   
    NULL, // V   
    NULL, // W   
    NULL, // X   
    NULL, // Y   
    NULL, // Z   
    NULL, // [   
    NULL, /* \\ */
    NULL, // ]   
    NULL, // ^   
    NULL, // _   
    NULL, // `   
    &bt_char_a, // a   
    &bt_char_b, // b   
    &bt_char_c, // c   
    &bt_char_d, // d   
    &bt_char_e, // e   
    &bt_char_f, // f   
    &bt_char_g, // g
    &bt_char_h, // h
    &bt_char_i, // i
    &bt_char_j, // j
    &bt_char_k, // k
    &bt_char_l, // l
    &bt_char_m, // m
    &bt_char_n, // n
    &bt_char_o, // o
    &bt_char_p, // p
    &bt_char_q, // q
    &bt_char_r, // r
    &bt_char_s, // s
    &bt_char_t, // t
    &bt_char_u, // u
    &bt_char_v, // v
    &bt_char_w, // w
    &bt_char_x, // x
    &bt_char_y, // y
    &bt_char_z, // z
    NULL, // {
    NULL, // |
    NULL, // }
    NULL, // ~
    NULL, // DEL
  }
};

