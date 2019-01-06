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
  Print(
    L"DEBUG: fill_rect at %d,%d+%dx%d\n",
    rect.x,
    rect.y,
    rect.w,
    rect.h);

  UINT32 x0 = rect.x, y0 = rect.y;
  for(UINT32 x = x0; x < x0 + rect.w; x++) {
    for(UINT32 y = y0; y < y0 + rect.h; y++) {
      SET_BUFFER_PIXEL(lfb, x, y, color);
    }
  }
}

void screen_buffer_clear(LFB * const lfb, bgr color) {
  Print(L"DEBUG: cleared screen buffer.\n");
  for(int i = 0; i < lfb->width * lfb->height; i++) {
    lfb->buffer[i] = color;
  }
}

void screen_buffer_copy(LFB * const lfb) {
  for(int i = 0; i < lfb->width * lfb->height; i++) {
    lfb->pixels[i] = lfb->buffer[i];
  }
}

#if MOCK_LFB
mock_vram_t mock_vram = {};
#endif
