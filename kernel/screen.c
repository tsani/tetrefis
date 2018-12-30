#include "screen.h"

void fill_rect(LFB * const lfb, rect rect, bgr color) {
  UINT32 x0 = rect.x, y0 = rect.y;
  for(UINT32 x = x0; x < x0 + rect.w; x++) {
    for(UINT32 y = y0; y < y0 + rect.h; y++) {
      SET_PIXEL(lfb, x, y, color);
    }
  }
}

const bgr WHITE = {
  .blue = 255,
  .green = 255,
  .red = 255,
  .unused = 0
};
