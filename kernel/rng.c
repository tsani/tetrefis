#include "rng.h"

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

UINT32 next_uint32(RNG * const rng) {
  UINT32 r = (rng->multiplier * rng->state + rng->increment) % rng->modulus;
  rng->state = r;
  return r;
}
