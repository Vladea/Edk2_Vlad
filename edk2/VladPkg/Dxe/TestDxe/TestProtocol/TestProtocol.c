#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include "Include/Protocol/VladProtocolInfo.h"

EFI_STATUS
VladTestProtocolEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS         Status;
  VLAD_TEST_PROTOCOL *ProtocolTest;
  CHAR16             *Name;
  UINT16             Reversion;

  Reversion        = 0xDCBA;
  ProtocolTest     = NULL;
  Name             = L"VLDc";
  DEBUG ((DEBUG_INFO, "[VladTestProtocol] VladTestProtocolEntry  Started\n"));
  Status = gBS->LocateProtocol (
                  &gVladProtocolInfoGuid,
                  NULL,
                  (VOID **)&ProtocolTest
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "[VladTestProtocol] LocateProtocol failed: %r\n", Status));
    return Status;
  }
  if (ProtocolTest == NULL || ProtocolTest->SayHelloWorld == NULL) {
    DEBUG ((DEBUG_ERROR, "[VladTestProtocol] Invalid protocol interface\n"));
    return EFI_INVALID_PARAMETER;
  }

  Status = ProtocolTest->SayHelloWorld(ProtocolTest);
  DEBUG ((DEBUG_INFO, "[VladTestProtocol] ProtocolTest->FieldA = 0x%x\n", ProtocolTest->FieldA));
  Status = ProtocolTest->UpdateVersion(ProtocolTest, Reversion);
  DEBUG ((DEBUG_INFO, "[VladTestProtocol] After update , out func , ProtocolTest->Reversion = 0x%x\n", ProtocolTest->Revision));
  DEBUG ((DEBUG_INFO, "%s is %s", Name, PcdGetBool(PcdLifeStatus) ? 'Live' : 'Dead'));
  return Status;
}
