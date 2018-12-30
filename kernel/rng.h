#ifndef RNG_H
#define RNG_H

#include <efi.h>

/**
 * \brief
 * Wraps an EFI RNG protocol.
 */
typedef struct RNG {
  EFI_RNG_PROTOCOL * const protocol;
} RNG;

/**
 * \brief
 * Gets one random byte.
 */
UINT8 random_byte(RNG * const rng);

#endif
