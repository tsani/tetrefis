#include "screen.h"

const bgr WHITE = BGR(255, 255, 255);
const bgr RED = BGR(0, 0, 255);
const bgr BLUE = BGR(255, 0, 0);
const bgr GREEN = BGR(0, 255, 0);
const bgr BLACK = BGR(0, 0, 0);

void fill_rect(LFB * const lfb, rect rect, bgr color) {
  // Print(
  //   L"DEBUG: fill_rect at %d,%d+%dx%d\n",
  //   rect.x,
  //   rect.y,
  //   rect.w,
  //   rect.h);

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

/**
 * \brief
 * Static space to use for the mock video memory.
 */
static mock_vram_t mock_vram = {};

/**
 * \brief
 * Loads an LFB that just does draws into memory and doesn't set the
 * video mode.
 * This can be used for debugging, as Print and so on will still work.
 */
LFB
load_lfb(EFI_STATUS * status) {
  *status = EFI_SUCCESS;
  return (LFB) {
    .pixels = mock_vram.data,
    .buffer = SCREEN_BUFFER.data,
    .width = SCREEN_WIDTH,
    .height = SCREEN_HEIGHT,
    .pixels_per_scanline = 1
  };
}

#else
// real graphics mode setup

/**
 * \brief
 * Decide whether a given graphics mode has the required resolution.
 */
static int
mode_is_suitable(
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION const * const info) {
  //
  UINTN h = info->VerticalResolution;
  UINTN w = info->HorizontalResolution;
  Print(L"Trying %dx%d\n", w, h);
  return w == SCREEN_WIDTH && h == SCREEN_HEIGHT &&
    info->PixelFormat == PixelBlueGreenRedReserved8BitPerColor;
}

/**
 * \brief
 * Enumerates video modes until one satisfying `mode_is_suitable` is
 * found, and sets the active mode to that mode.
 */
static EFI_STATUS
find_and_set_video_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL * const gop) {
  EFI_STATUS status;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
  UINTN info_size;

  // enumerate available video modes
  for(int mode_i = 0; mode_i < gop->Mode->MaxMode; mode_i++) {
    if(EFI_ERROR(
         (status =
          gop->QueryMode(gop, mode_i, &info_size, &info))))
      return status;
    
    if(!mode_is_suitable(info)) {
      continue;
    }

    return gop->SetMode(gop, mode_i);
  }

  return EFI_NOT_FOUND;
}

/**
 * \brief
 * Prepares the linear frame buffer by finding the GOP and setting the
 * video mode.
 *
 * Unconditionally sets *_status. The return value is undefined if
 * EFI_ERROR(*_status) is true.
 */
LFB
load_lfb(EFI_STATUS * status) {
  EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

  if(EFI_ERROR(
       (*status =
       ST->BootServices->LocateProtocol(
         &gop_guid,
         NULL,
         (void**)&gop)))) {
    Print(L"FATAL: failed to locate GOP.\n");
    return (LFB) {};
  }
     
  Print(L"Framebuffer base is at %lx\n", gop->Mode->FrameBufferBase);
  Print(L"Finding a suitable video mode; preferred resolution: 640x480.\n");

  if(EFI_ERROR((*status = find_and_set_video_mode(gop))))
    return (LFB) {};

  *status = EFI_SUCCESS;
  return (LFB) {
    .pixels = (bgr*) gop->Mode->FrameBufferBase,
    .buffer = SCREEN_BUFFER.data,
    .width = gop->Mode->Info->HorizontalResolution,
    .height = gop->Mode->Info->VerticalResolution,
    .pixels_per_scanline = gop->Mode->Info->PixelsPerScanLine
  };
}

#endif
