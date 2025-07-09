/** @file
  Vlad Test Dxe Protocol.

**/

#ifndef __VLAD_PROTOCOL_INFO_PROTOCOL_H__
#define __VLAD_PROTOCOL_INFO_PROTOCOL_H__

#define VLAD_PROTOCOL_INFO_PROTOCOL_GUID  \
{ 0xbb84a4ef, 0x3c4f, 0x410e, { 0xb6, 0xe, 0xf9, 0x7, 0xab, 0xf9, 0xb4, 0x38 } }

typedef struct {
  UINT16        FieldA;
  UINT16        FieldB;
  } TEST_PROTOCOL;

extern EFI_GUID gVladProtocolInfoGuid;

#endif