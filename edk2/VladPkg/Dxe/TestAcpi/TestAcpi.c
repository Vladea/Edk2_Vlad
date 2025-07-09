/** @file

SPDX-License-Identifier: BSD-2-Clause-Patent

**/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/AcpiTable.h>
#include <Library/DxeServicesLib.h>

EFI_STATUS
EFIAPI
InstallSsdtTable (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                   Status;
  EFI_ACPI_TABLE_PROTOCOL      *AcpiTableProtocol;
  EFI_ACPI_DESCRIPTION_HEADER  *SsdtTable;
  UINTN                        SsdtTableSize;
  UINTN                        TableKey;

  // Locate the ACPI Table Protocol
  Status = gBS->LocateProtocol(&gEfiAcpiTableProtocolGuid, NULL, (VOID **)&AcpiTableProtocol);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a, Failed to locate ACPI Table Protocol: %r\n", __func__, Status));
    return Status;
  }

  // Locate the SSDT table from the firmware volume using GetSectionFromFv
  Status = GetSectionFromFv(&gEfiCallerIdGuid, EFI_SECTION_RAW, 0, (VOID **)&SsdtTable, &SsdtTableSize);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a, Failed to get SSDT table from firmware volume: %r\n", __func__, Status));
    return Status;
  }

  // Install the SSDT table
  Status = AcpiTableProtocol->InstallAcpiTable(AcpiTableProtocol, SsdtTable, SsdtTable->Length, &TableKey);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a, Failed to install SSDT table: %r\n", __func__, Status));
    FreePool(SsdtTable);
    return Status;
  }

  DEBUG((EFI_D_ERROR, "%a, SSDT table installed successfully\n", __func__));
  FreePool(SsdtTable);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestAcpiEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  DEBUG((EFI_D_ERROR, "%a, entered\n", __func__));
  return InstallSsdtTable(ImageHandle, SystemTable);
}