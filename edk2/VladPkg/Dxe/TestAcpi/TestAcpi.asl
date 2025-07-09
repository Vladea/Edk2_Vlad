/** @file

SPDX-License-Identifier: BSD-2-Clause-Patent

**/
DefinitionBlock (
  "TestAcpi.aml", // Output File Name
  "SSDT",         // Signature
  2,              // Version
  "OEMID",        // OEM ID
  "OEMTABLE",     // OEM Table ID
  0x00000001      // OEM Revision
  )
{
  Scope (\_SB)
  {
    Device (TEST)
    {
      Name (_HID, "ACPI0012")
      Name (_STR, Unicode ("Test ACPI Device"))
      Method (_STA, 0)
      {
        Return (0x0f)
      }
    }
  }
}