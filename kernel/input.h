#ifndef INPUT_H
#define INPUT_H

#include <efi.h>
#include <efilib.h>

#include "config.h"

typedef enum READ_INPUT_KEY_STATUS {
  INPUT_KEY_NONE, // no input key
  INPUT_KEY_ERROR, // failed to read
  INPUT_KEY_SUCCESS // successfully read
} READ_INPUT_KEY_STATUS;

typedef enum INPUT_KEY {
  MOVE_LEFT = 0,
  MOVE_RIGHT,
  ROTATE_CCW,
  ROTATE_CW,
  FALL,
  QUIT,
  UNKNOWN,
  INPUT_KEY_MAX
} INPUT_KEY;

typedef struct input_manager_t {
  EFI_SIMPLE_TEXT_IN_PROTOCOL * const protocol;
} input_manager_t;

/**
 * \brief
 * Loads an input manager from UEFI.
 */
input_manager_t load_input_manager(EFI_STATUS * status);

/**
 * \brief
 * Reads a key.
 *
 * \returns
 * - `1` if a key was read.
 * - `0` if no key was read.
 * - `-1` if an error occurred.
 */
READ_INPUT_KEY_STATUS read_input_key(
  input_manager_t * const input,
  INPUT_KEY * const key);

#endif
