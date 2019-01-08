#include "text.h"

void
bt_render_string(
  bt_renderer_info * const renderer_info,
  char const * const str) {
  //
  // TODO
  //
}

//////////////////////
// DATA DEFINITIONS //
//////////////////////

// Prepare yourself for some SHIT.

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
    &bt_char_1, // 1
    &bt_char_2, // 2   
    &bt_char_3, // 3
    &bt_char_4, // 4   
    &bt_char_5, // 5
    &bt_char_6, // 6   
    &bt_char_7, // 7
    &bt_char_8, // 8   
    &bt_char_9, // 9
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
  .height = 6,
  .baseline = 5,
  .data = {
    X,
    n,
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
    X, n, n, X, X,
    X, n, n, X, n,
    X, n, n, n, X,
    X, n, n, n, X
  }
};

bt_char const bt_char_l = {
  .width = 5,
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
  .baseline = 6,
  .data = {
    X, X, n, X, X, n, n,
    X, n, X, X, n, X, n,
    X, n, n, X, n, n, X,
    X, n, n, X, n, n, X,
    X, n, n, X, n, n, X,
    X, n, n, n, n, n, X,
    X, n, n, n, n, n, X
  }
};

bt_char const bt_char_n = {
  .width = 4,
  .height = 6,
  .baseline = 5,
  .data = {
    X, X, n, n,
    X, n, X, n,
    X, n, n, X,
    X, n, n, X,
    X, n, n, X,
    X, n, n, n,
    X, n, n, n
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
  .width = 6,
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
  .width = 6,
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
    X, X, X, n,
    X, n, n, X,
    X, n, n, n,
    n, X, X, n,
    n, n, n, X,
    X, n, n, X,
    n, X, X, n
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

