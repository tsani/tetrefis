#include "rng.h"

UINT8 random_byte(RNG * const rng) {
  UINT8 b;
  rng->protocol->GetRNG(rng->protocol, NULL, 1, &b);
  return b;
}
