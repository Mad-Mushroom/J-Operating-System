#include "kernel.h"

#define D_VGA_MEMORY (char*)0xb8000

extern void main(){
    *(D_VGA_MEMORY) = 'A';
    return;
}