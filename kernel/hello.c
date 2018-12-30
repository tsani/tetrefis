#include <efi.h>
#include <efilib.h>

#include "screen.h"
#include "tetris.h"

// void await_key() {
//   EFI_STATUS status;
//   EFI_INPUT_KEY key;
//   while ((status = ST->ConIn->ReadKeyStroke(ST->ConIn, &key)) == EFI_NOT_READY) ;
// }

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
    .width = gop->Mode->Info->HorizontalResolution,
    .height = gop->Mode->Info->VerticalResolution,
    .pixels_per_scanline = gop->Mode->Info->PixelsPerScanLine
  };
}

RNG
load_rng(EFI_STATUS * status) {
  EFI_RNG_PROTOCOL *rngp;
  EFI_GUID rngp_guid = EFI_RNG_PROTOCOL_GUID;
  
  
  if(EFI_ERROR(
       (*status =
       ST->BootServices->LocateProtocol(
         &rngp_guid,
         NULL,
         (void**)&rngp)))) {
    Print(L"FATAL: failed to locate RNG protocol.\n");
    return (RNG) {};
  }

  *status = EFI_SUCCESS;
  return (RNG) {
    .protocol = rngp
  };
}
 
EFI_STATUS
efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
  EFI_STATUS status;

  InitializeLib(image_handle, system_table);
  Print(L"Welcome to tetrEFIs!\n");

  LFB lfb = load_lfb(&status);
  if(EFI_ERROR(status))
    return status;

  RNG rng = load_rng(&status);
  if(EFI_ERROR(status))
    return status;

  game_state s = make_initial_state(&lfb, &rng);

  // TODO disable the watchdog timer

  // not sure if RNG will continue to work after exiting boot services
  // (probably not)
  // ST->BootServices->ExitBootServices();
  return game(&s);
}
