#include "screen.h"

const bgr WHITE = {
  .blue = 255,
  .green = 255,
  .red = 255,
  .unused = 0
};

const bgr RED = {
  .blue = 0,
  .green = 0,
  .red = 255,
  .unused = 0
};

const bgr BLUE = {
  .blue = 255,
  .green = 0,
  .red = 0,
  .unused = 0
};

const bgr GREEN = {
  .blue = 0,
  .green = 255,
  .red = 0,
  .unused = 0
};

const bgr BLACK = {
  .blue = 0,
  .green = 0,
  .red = 0,
  .unused = 0
};

void fill_rect(LFB * const lfb, rect rect, bgr color) {
  UINT32 x0 = rect.x, y0 = rect.y;
  for(UINT32 x = x0; x < x0 + rect.w; x++) {
    for(UINT32 y = y0; y < y0 + rect.h; y++) {
      SET_PIXEL(lfb, x, y, color);
    }
  }
}

void lfb_clear(LFB * const lfb, bgr color) {
  fill_rect(lfb, (rect) { 0, 0, lfb->width, lfb->height }, color);
}
