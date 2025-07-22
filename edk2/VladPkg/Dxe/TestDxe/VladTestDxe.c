#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include "Include/Protocol/VladProtocolInfo.h"

VLAD_TEST_PROTOCOL  mVladProtocol;

//extern gVladVariableGuid = { 0xea9408df, 0xf4d9, 0x49dc, { 0xa7, 0x31, 0xf4, 0x56, 0x71, 0xe1, 0xb7, 0x10 } };


EFI_STATUS
EFIAPI
SayHelloWorld (
  VLAD_TEST_PROTOCOL *This
  )
{
  DEBUG ((DEBUG_INFO, "[VladTestDxe] Hello world, Happy %d years birthday\n", This->FieldB));
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UpdateVersion (
  VLAD_TEST_PROTOCOL *This
) {
  DEBUG ((DEBUG_INFO, "[VladTestDxe] Before Update ,Reversion is %x\n", This->Revision));
  This->Revision = 0xDCBA;
  DEBUG ((DEBUG_INFO, "[VladTestDxe] After Update ,Reversion be like in func:  0x%x\n", This->Revision));
  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
VladTestDxeEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  VladTestHandle;
  UINT32      VladVariable;

  VladTestHandle = NULL;
  VladVariable   = 0x0824;
  mVladProtocol.FieldA = 0x09;
  mVladProtocol.FieldB = 0x2A;
  mVladProtocol.SayHelloWorld = SayHelloWorld;
  mVladProtocol.Revision = 0xABCD;
  mVladProtocol.UpdateVersion = UpdateVersion;

  Status = gRT->SetVariable(
    L"VladVariable",
    &gVladVariableGuid,
    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
    sizeof (VladVariable),
    &VladVariable
    );
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "[VladTestDxe] Set Variable Status is %r.\n", Status));
    DEBUG ((DEBUG_INFO, "[VladTestDxe] Set Variable Success | VladVariable Data is 0x%x.\n", VladVariable));
  } else {
    DEBUG ((DEBUG_ERROR, "[VladTestDxe] Set Variable Status is %r.\n", Status));
    DEBUG ((DEBUG_ERROR, "[VladTestDxe] Set Variable Failed | VladVariable is 0x%x.\n", VladVariable));
  }

  Status = gBS->InstallProtocolInterface (
                  &VladTestHandle,
                  &gVladProtocolInfoGuid,
                  EFI_NATIVE_INTERFACE,
                  &mVladProtocol
                  );
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "[VladTestDxe] Install Protocol Status is %r.\n", Status));
    DEBUG ((DEBUG_INFO, "[VladTestDxe] Install Protocol Success | mVladProtocol.FieldA is 0x%x.\n", mVladProtocol.FieldA));
    DEBUG ((DEBUG_INFO, "[VladTestDxe] Install Protocol Success | mVladProtocol.FieldB is 0x%x.\n", mVladProtocol.FieldB));
  } else {
    DEBUG ((DEBUG_ERROR, "[VladTestDxe] Install Protocol Status is %r.\n", Status));
    DEBUG ((DEBUG_ERROR, "[VladTestDxe] Install Protocol Failed.\n"));
  }

  return Status;
}