/** @file
  Vlad Test Dxe Protocol.

**/

#ifndef __VLAD_PROTOCOL_INFO_PROTOCOL_H__
#define __VLAD_PROTOCOL_INFO_PROTOCOL_H__

typedef struct _VLAD_TEST_PROTOCOL VLAD_TEST_PROTOCOL;

typedef EFI_STATUS (EFIAPI *VLAD_HELLO_WORLD) (
  IN VLAD_TEST_PROTOCOL *This
);

typedef EFI_STATUS (EFIAPI *VLAD_UPDATE_VERSION) (
  IN VLAD_TEST_PROTOCOL *This,
  IN UINT16             Reversion
);


struct _VLAD_TEST_PROTOCOL{
  UINT16                Revision;
  VLAD_HELLO_WORLD      SayHelloWorld;
  VLAD_UPDATE_VERSION   UpdateVersion;
  UINT16        FieldA;
  UINT16        FieldB;
};

extern EFI_GUID gVladProtocolInfoGuid;

#endif