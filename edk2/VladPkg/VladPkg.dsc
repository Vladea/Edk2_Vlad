## @file  VladPkg.dsc
# This package just for personal learn.
#
##

[Defines]
  PLATFORM_NAME                  = VladPkg
  PLATFORM_GUID                  = CF6C4158-753E-424F-BD29-7C33AEB29A4E
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/VladPkg
  SUPPORTED_ARCHITECTURES        = IA32|X64|EBC|ARM|AARCH64|RISCV64
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT

[LibraryClasses]

[Components]

[BuildOptions]
  *_*_*_CC_FLAGS = -D DISABLE_NEW_DEPRECATED_INTERFACES