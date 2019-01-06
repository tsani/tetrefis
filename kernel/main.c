#include <efi.h>
#include <efilib.h>

#include "tetris.h"

EFI_STATUS
efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
  EFI_STATUS status;

  InitializeLib(image_handle, system_table);
  Print(L"Welcome to tetrEFIs!\n");

  RNG rng = load_rng(&status);
  if(EFI_ERROR(status))
    return status;

  LFB lfb = load_lfb(&status);
  if(EFI_ERROR(status))
    return status;

  input_manager_t input_manager = load_input_manager(&status);
  if(EFI_ERROR(status)) {
    return status;
  }

  Print(L"DEBUG: loaded all services\n");

  // fill_rect(
  //   &lfb,
  //   (rect) { .x = 0, .y = 0, .w = SCREEN_WIDTH, .h = SCREEN_HEIGHT },
  //   BLACK);

  int ok;
  game_state s = make_initial_state(&ok, &lfb, &rng, &input_manager);
  if(!ok)
    return -1;

  // TODO disable the watchdog timer

  // not sure if RNG will continue to work after exiting boot services
  // (probably not)
  // ST->BootServices->ExitBootServices();
  game(&s);
  return EFI_SUCCESS;
}
