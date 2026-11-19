#clang -O2 -ffreestanding -nostdlib -fno-builtin --target=x86_64-windows-msvc -fuse-ld=lld-link -Wl,-entry:efi_main -Wl,-subsystem:efi_application -I./sys/posix-uefi/uefi -o BootX64.efi  Bootx64.c ./sys/posix-uefi/uefi/*.c 
#Build
if [ "$1" = "-wEnable" ]; then
    echo -e "\033[35m"
    echo -e "Building Dependencies"
    echo -e "\033[35m"
    gcc -m64 -ffreestanding -c kernel.c -o kernel.o
    gcc -m64 -ffreestanding -c sys/stdio.c -o stdio.o
    gcc -m64 -ffreestanding -c sys/features.c -o features.o
    gcc -m64 -ffreestanding -c sys/acpi.c -o acpi.o
    gcc -m64 -ffreestanding -c sys/stdlib.c -o stdlib.o
    gcc -m64 -ffreestanding -c kernel.c -o kernel.o
    echo -e "Linking"
    echo -e '\033[31m'
    ld -m elf_x86_64 -T linker.ld kernel.o stdio.o features.o acpi.o stdlib.o -o kernel.elf
    objcopy -O binary kernel.elf kernel.bin
    cd EFIBuild
    echo -e "\033[35m"
    make
    cd -
    #Prepping Disk
    echo -e "Prepping Disk"
    cp -f EFIBuild/BootX64.efi efi_disk/EFI/BOOT
    cp -f kernel.bin efi_disk/EFI/BOOT
    #Cleanup
    echo -e "\033[35m;Cleaning Up"
    rm *.o
    rm *.bin
    qemu-system-x86_64 -bios /usr/share/qemu/OVMF.fd -drive file=fat:rw:efi_disk,format=raw
    echo -e "\033[37m"
    exit 1
fi
echo -e "\033[35mTo Unsupress Build Warnings Pass -wEnable; ex: ./Build.sh -wEnable "
echo -e "\033[35m"
echo -e "Building Dependencies"
echo -e "\033[35m"
gcc -m64 -w -ffreestanding -c kernel.c -o kernel.o
gcc -m64 -w -ffreestanding -c sys/stdio.c -o stdio.o
gcc -m64 -w -ffreestanding -c sys/features.c -o features.o
gcc -m64 -w -ffreestanding -c sys/acpi.c -o acpi.o
gcc -m64 -w -ffreestanding -c sys/stdlib.c -o stdlib.o
gcc -m64 -w -ffreestanding -c kernel.c -o kernel.o
echo -e "Linking"
echo -e '\033[31m'
ld -m elf_x86_64 -T linker.ld kernel.o stdio.o features.o acpi.o stdlib.o -o kernel.elf
objcopy -O binary kernel.elf kernel.bin
cd EFIBuild
echo -e "\033[35m"
make
cd -
#Prepping Disk
echo -e "Prepping Disk"
cp -f EFIBuild/BootX64.efi efi_disk/EFI/BOOT
cp -f kernel.bin efi_disk/EFI/BOOT
#Cleanup
echo -e "\033[35m;Cleaning Up"
rm *.o
rm *.bin
rm *.elf
qemu-system-x86_64 -bios /usr/share/qemu/OVMF.fd -drive file=fat:rw:efi_disk,format=raw
echo -e "\033[37m"

