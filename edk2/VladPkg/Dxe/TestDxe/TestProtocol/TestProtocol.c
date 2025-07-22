#include <PiDxe.h>
#include <Library/BaseLib.h>
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
  
  DEBUG ((DEBUG_INFO, "[VladTestProtocol] Hello from Vlad Protocol\n"));
  DEBUG ((DEBUG_INFO, "[VladTestProtocol] ProtocolTest->FieldA = 0x%x\n", ProtocolTest->FieldA));
  Status = ProtocolTest->SayHelloWorld(ProtocolTest);
  Status = ProtocolTest->UpdateVersion(ProtocolTest);
  DEBUG ((DEBUG_INFO, "[VladTestProtocol] After update , out func , ProtocolTest->Reversion = 0x%x\n", ProtocolTest->Revision));
  return Status;
}
