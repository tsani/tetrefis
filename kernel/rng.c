#include "rng.h"

#include <efilib.h>

UINT32 const BSD_MODULUS = 2147483648;
UINT32 const BSD_INCREMENT = 12345;
UINT32 const BSD_MULTIPLIER = 1103515245;

RNG make_rng(UINT32 seed) {
  return (RNG) {
    .modulus = 2147483648,
    .increment = 12345,
    .multiplier = 1103515245,
    .state = seed
  };
}

RNG load_rng(EFI_STATUS * status) {
  // create the initial seed by using the time
  EFI_TIME time;
  if(EFI_ERROR((*status = RT->GetTime(&time, NULL))))
    return (RNG) {};

  *status = EFI_SUCCESS;

  UINT32 s = (time.Hour * 60 + time.Minute * 60) + time.Second;
  return make_rng(s);
}

UINT32 next_uint32(RNG * const rng) {
  UINT32 r = (rng->multiplier * rng->state + rng->increment) % rng->modulus;
  rng->state = r;
  return r;
}
