#include <efi.h>
#include <efilib.h>

#include "time.h"

timer make_timer(int * ok, uint32_t duration_ms) {
  timer timer = {
    .duration_ms = duration_ms
  };
  
  *ok = !EFI_ERROR(
    BS->CreateEvent(
      EVT_TIMER,
      TPL_APPLICATION,
      NULL,
      NULL,
      &(timer.event)));

  return timer;
}

int await_timer(timer * const timer) {
  EFI_STATUS status;
  UINTN event_index;

  // 10000 is the number of times 100ns fits into 1ms.
  // SetTimer expects a time in units of 100ns bundles.
  // wtf.
  // Correction: an extra factor of 100 was added by experiment.
  if(EFI_ERROR(
       (status =
        BS->SetTimer(
          timer->event,
          TimerRelative,
          timer->duration_ms * 10000)))) {
    Print(L"Failed to set timer.\n");
    return status;
  }

  if(EFI_ERROR(
       (status =
        BS->WaitForEvent(1, &(timer->event), &event_index)))) {
    Print(L"Failed to await event.\n");
    return status;
  }

  return 1;
}
