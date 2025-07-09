#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include "Include/Protocol/VladProtocolInfo.h"

TEST_PROTOCOL mVladProtocol = {0x08, 0x24};

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