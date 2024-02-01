export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "src/boot/boot.asm" -f bin -o "bin/boot.bin"
nasm "src/boot/kernel_entry.asm" -f elf -o "bin/kernel_entry.o"
# for f in ./src/*.c; do
#    i386-elf-gcc -ffreestanding -m32 -g -c $f -o "bin/c/$f.o"
# done
find ./src/*.c -type f -exec i386-elf-gcc -ffreestanding -m32 -g -c {} -o bin/c/IDK.o \;
# i386-elf-gcc -ffreestanding -m32 -g -c "src/kernel.c" -o "bin/c/kernel.o"
nasm "src/boot/idt.asm" -f elf -o "bin/idt.o"
nasm "src/boot/zeroes.asm" -f bin -o "bin/zeroes.bin"

i386-elf-ld -o "bin/full_kernel.bin" -Ttext 0x1000 "bin/kernel_entry.o" "bin/c/*.o" "bin/idt.o" --oformat binary

cat "bin/boot.bin" "bin/full_kernel.bin" "bin/zeroes.bin"  > "bin/OS.bin"

qemu-system-x86_64 -drive format=raw,file="bin/OS.bin",index=0,if=floppy,  -m 128M