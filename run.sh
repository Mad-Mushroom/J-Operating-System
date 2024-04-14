export PATH="$PATH:/usr/local/x86_64elfgcc/bin"

nasm src/boot/bootloader.asm -f bin -o bin/bootloader.bin
nasm src/boot/ExtendedProgram.asm -f elf64 -o bin/ExtendedProgram.o
nasm src/boot/Binaries.asm -f elf64 -o bin/Binaries.o
x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -c "src/Kernel.cpp" -o "bin/Kernel.o"
x86_64-elf-ld -T"src/link.ld"

cat bin/bootloader.bin bin/kernel.bin > bin/jOS.bin

dd if=/dev/zero of=bin/jos_formated.bin bs=512 count=2440 >/dev/null
dd if=bin/jOS.bin of=bin/jos_formated.bin conv=notrunc >/dev/null

qemu-system-x86_64 -drive format=raw,file="bin/jos_formated.bin",index=0,if=floppy,  -m 128M -audiodev coreaudio,id=audio0 -machine pcspk-audiodev=audio0