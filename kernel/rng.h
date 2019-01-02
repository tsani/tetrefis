#ifndef RNG_H
#define RNG_H

#include <efi.h>

UINT32 const BSD_MODULUS;
UINT32 const BSD_INCREMENT;
UINT32 const BSD_MULTIPLIER;

/**
 * \brief
 * A linear congruential PRNG's parameters and state.
 */
typedef struct RNG {
  UINT32 const modulus;
  UINT32 const increment;
  UINT32 const multiplier;
  UINT32 state;
} RNG;

/**
 * \brief
 * Construct a linear congruential PRNG.
 */
RNG make_rng(UINT32 seed);

/**
 * \brief
 * Gets one random UINT32 using the BSD algorithm.
 * Note that the UINT32's MSB will always be zero, so in fact the number is in the range
 * [0, 2^31).
 */
UINT32 next_uint32(RNG * const rng);

#endif
