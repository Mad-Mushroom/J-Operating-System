[org 0x7c00]

mov [BOOT_DISK], dl

mov bp, 0x7c00
mov sp, bp

mov bx, BootString
call PrintString

call ReadDisk

jmp PROGRAM_SPACE

%include "src/boot/print.asm"
%include "src/boot/DiskRead.asm"

jmp $

times 510-($-$$) db 0

dw 0xaa55