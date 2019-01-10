#include "input.h"

input_manager_t load_input_manager(EFI_STATUS * status) {
  // EFI_GUID input_protocol_guid = EFI_SIMPLE_TEXT_IN_PROTOCOL_GUID;
  // EFI_SIMPLE_TEXT_IN_PROTOCOL *protocol;
  // *status = BS->LocateProtocol(
  //   &input_protocol_guid,
  //   NULL,
  //   &protocol);
  return (input_manager_t) {
    .protocol = ST->ConIn
  };
}

READ_INPUT_KEY_STATUS read_input_key(
  input_manager_t * const input,
  INPUT_KEY * const key) {
  //
  EFI_INPUT_KEY data;
  EFI_STATUS status;

  Print(L"DEBUG: reading input\n");

  status = input->protocol->ReadKeyStroke(
    input->protocol,
    &data);

  if(status == EFI_NOT_READY)
    return INPUT_KEY_NONE;
  else if(EFI_ERROR(status))
    return INPUT_KEY_ERROR;

  // otherwise a key was in fact read

  switch(data.ScanCode) {
  case 0x02:
    *key = MOVE_DOWN;
    return INPUT_KEY_SUCCESS;
  case 0x03:
    *key = MOVE_RIGHT;
    return INPUT_KEY_SUCCESS;
  case 0x04:
    *key = MOVE_LEFT;
    return INPUT_KEY_SUCCESS;
  }

  switch(data.UnicodeChar) {
  case L' ':
    *key = FALL;
    return INPUT_KEY_SUCCESS;
  case L'z':
    *key = ROTATE_CCW;
    return INPUT_KEY_SUCCESS;
  case L'x':
    *key = ROTATE_CW;
    return INPUT_KEY_SUCCESS;
  case L'q':
    *key = QUIT;
    return INPUT_KEY_SUCCESS;
  }

  *key = UNKNOWN;
  return INPUT_KEY_SUCCESS;
}
