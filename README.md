# <center>Edk2_Vlad<center> #
### <u>For Bios Learning, Ovmf and Emulator are supported</u>

Environment used as follow: 

Edk2 : https://github.com/tianocore/edk2/tree/edk2-stable202505

VS compiler : VS2017/19

NASM :  https://nasm.us/ (Environment variable : set NASM_PREF=C:\nasm\ )

IASL : https://acpica.org/downloads (C:\ASL\ )

OpenSSL : https://github.com/openssl/openssl/releases (C:\openssl\ )

Python : https://www.python.org/ (Version 3.8 or later)

Qemu : https://qemu.weilnetz.de/w64/2022/



Edk Base Tool (optional) : https://github.com/tianocore/edk2-BaseTools-win32

<br/>

### How to Build Emulator / Ovmf:


set WORKSPACE=%CD%

set PACKAGES_PATH=%WORKSPACE%\edk2

cd edk2

edksetup.bat

edksetup.bat rebuild   //nmake -f %BASE_TOOLS_PATH%\Makefile

build -a X64 -t VS2017 -p EmulatorPkg\EmulatorPkg.dsc -D DEBUG_ON_SERIAL_PORT

build -a X64 -t VS2017 -p OvmfX64Pkg\OvmfX64Pkg.dsc -D DEBUG_ON_SERIAL_PORT


<br/>

### How to Run OVMF Bios:

After build OvmfPkg, you can find OVMF.fd under Build/OvmfX64/DEBUG_VS2017/FV , which  can be placed into OVMF root folder, than run as next :

qemu-system-x86_64.exe -bios OVMF.fd -serial stdio -hda fat:rw:F:\OvmfTemp -net none 

qemu-system-x86_64.exe -pflash OVMF.fd -serial stdio -hda fat:rw:F:\OvmfTemp -net none

<br/>

### How to Run OVMF Bios With a Ubuntu Os:

#### 1.Create a virtual disk

qemu>qemu-img create -f qcow2 F:\VirtualMachines\Ovmf_Ubuntu\ubuntu-disk.qcow2 20G

#### 2.Start QEMU to install Ubuntu:

qemu-system-x86_64 -pflash F:\VirtualMachines\Ovmf_Ubuntu\OVMF.fd -m  4096 -smp 4 -cdrom F:\OsImage\ubuntu-22.04-desktop-amd64.iso -drive  file=F:\VirtualMachines\Ovmf_Ubuntu\ubuntu-disk.qcow2,format=qcow2  -vga virtio -netdev user,id=net0 -device e1000,netdev=net0 -usb -device  usb-tablet

**Here we allocate 4GB of memory; use a 4-core CPU; use user mode  networking, specify an e1000 network card; enable a USB mouse, and use  Ubuntu 22.04 ISO as the installation disc.** **The BIOS uses the Binary of OVMF that you compiled**.

#### 3.After installation, you can directly boot from the virtual disk:

qemu-system-x86_64 -pflash F:\VirtualMachines\Ovmf_Ubuntu\OVMF.fd -hda  fat:rw:F:\OvmfTemp -m 4096 -smp 4 -drive  file=F:\VirtualMachines\Ovmf_Ubuntu\ubuntu-disk.qcow2,format=qcow2  -vga virtio  -netdev user,id=net0 -device e1000,netdev=net0  -usb -device  usb-tablet -chardev  stdio,id=char0,logfile=F:\VirtualMachines\Ovmf_Ubuntu\serial.log,signal=off  -serial chardev:char0





