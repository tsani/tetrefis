#include <efi.h>
#include <efilib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct bgr {
  UINT8 blue;
  UINT8 green;
  UINT8 red;
  UINT8 unused;
} bgr;

bgr WHITE = {
  .blue = 255,
  .green = 255,
  .red = 255,
  .unused = 0
};

typedef struct rect {
  UINT32 x;
  UINT32 y;
  UINT32 w;
  UINT32 h;
} rect;

// base address of the linear frame buffer
bgr *LFB;
UINTN LFB_SIZE;
UINTN PIXELS_PER_SCANLINE;

void set_pixel(UINT32 x, UINT32 y, bgr p) {
  LFB[x + SCREEN_WIDTH * y] = p;
}

void fill_rect(rect rect, bgr color) {
  UINT32 x0 = rect.x, y0 = rect.y;
  for(UINT32 x = x0; x < x0 + rect.w; x++) {
    for(UINT32 y = y0; y < y0 + rect.h; y++) {
      set_pixel(x, y, color);
    }
  }
}

void await_key() {
  EFI_STATUS status;
  EFI_INPUT_KEY key;
  while ((status = ST->ConIn->ReadKeyStroke(ST->ConIn, &key)) == EFI_NOT_READY) ;
}

int
mode_is_suitable(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION const * const info) {
  UINTN h = info->VerticalResolution;
  UINTN w = info->HorizontalResolution;
  Print(L"Trying %dx%d\n", w, h);
  return w == 640 && h == 480 &&
    info->PixelFormat == PixelBlueGreenRedReserved8BitPerColor;
}

EFI_STATUS
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
 
EFI_STATUS
efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
  EFI_STATUS status;
  // EFI_INPUT_KEY key;
  EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
  
  InitializeLib(image_handle, system_table);
  
  Print(L"Hello world!\n");
  
  if(EFI_ERROR(
       (status =
       ST->BootServices->LocateProtocol(
         &gop_guid,
         NULL,
         (void**)&gop)))) {
    Print(L"FATAL: failed to locate GOP.\n");
    return status;
  }
     
  Print(L"Framebuffer base is at %lx\n", gop->Mode->FrameBufferBase);
  Print(L"Finding a suitable video mode; preferred resolution: 640x480.\n");

  if(EFI_ERROR((status = find_and_set_video_mode(gop))))
    return status;

  LFB = (bgr*) gop->Mode->FrameBufferBase;
  LFB_SIZE = gop->Mode->FrameBufferSize;

  fill_rect((rect) { .x = 0, .y = 0, .w = 640, .h = 480 }, WHITE);
     
     // /* Say hi */
     // Status = ST->ConOut->OutputString(ST->ConOut, L"Hello World\n\r");
     // if (EFI_ERROR(Status))
     //     return Status;
     
     // /* Now wait for a keystroke before continuing, otherwise your
     //    message will flash off the screen before you see it.
     
     //    First, we need to empty the console input buffer to flush
     //    out any keystrokes entered before this point */
     // Status = ST->ConIn->Reset(ST->ConIn, FALSE);
     // if (EFI_ERROR(Status))
     //     return Status;
     
     // /* Now wait until a key becomes available.  This is a simple
     //    polling implementation.  You could try and use the WaitForKey
     //    event instead if you like */
     // while ((Status = ST->ConIn->ReadKeyStroke(ST->ConIn, &Key)) == EFI_NOT_READY) ;
     
  return status;
}
