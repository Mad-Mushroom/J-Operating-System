#pragma once

#include "../Kernel.h"

#define pVGA_MEMORY (char*)0xb8000
#define pVGA_WIDTH 80
#define pVGA_HEIGHT 25

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long long uint_64;

bool Shell_pausedE = false;

uint_16 pCursorPosition;

void poutb(unsigned short port, unsigned char val){
  asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void pPrintString(const char* str, uint_8 color = 0x40 | 0x0F){
  uint_8* charPtr = (uint_8*)str;
  uint_16 index = pCursorPosition;
  while(*charPtr != 0){
    switch (*charPtr) {
      case 10:
        index += pVGA_WIDTH;
        index -= index % pVGA_WIDTH;
        break;
      case 13:
        index -= index % pVGA_WIDTH;
        break;
      default:
      *(pVGA_MEMORY + index * 2) = *charPtr;
      *(pVGA_MEMORY + index * 2 + 1) = color;
      index++;
    }
    charPtr++;
  }
  pCursorPosition = index;
}

void kpanic(const char* msg){
  uint_64 ClearColor = 0x40 | 0x0F;
  uint_64 value =0;
  value += ClearColor << 8;
  value += ClearColor << 24;
  value += ClearColor << 40;
  value += ClearColor << 56;
  for (uint_64* i = (uint_64*)pVGA_MEMORY; i < (uint_64*)(pVGA_MEMORY + 4000); i++){
    *i = value;
  }
  poutb(0x3D4, 0x0F);
  poutb(0x3D5, (uint_8)(0 & 0xFF));
  poutb(0x3D4, 0x0E);
  poutb(0x3D5, (uint_8)((0 >> 8) & 0xFF));
  pCursorPosition = 8 * pVGA_WIDTH;
  for(int i=8; i<pVGA_HEIGHT; i++) pPrintString(":( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :(", 0x40 | 0x0C);

  pCursorPosition = 0;

  pPrintString(KPanicASCII);
  pPrintString("Details:\n");
  pPrintString(msg);
  pCursorPosition = pVGA_WIDTH * (pVGA_HEIGHT - 1);
  pPrintString("System halted.", 0x40 | 0x0E);
  poutb(0x3D4, 0x0F);
  poutb(0x3D5, (uint_8)(pVGA_WIDTH*pVGA_HEIGHT & 0xFF));
  poutb(0x3D4, 0x0E);
  poutb(0x3D5, (uint_8)((pVGA_WIDTH*pVGA_HEIGHT >> 8) & 0xFF));

  for(;;) asm("hlt");
}

void ncErr(const char* msg){
  uint_64 ClearColor = 0x0F | 0x90;
  uint_64 value =0;
  value += ClearColor << 8;
  value += ClearColor << 24;
  value += ClearColor << 40;
  value += ClearColor << 56;
  for (uint_64* i = (uint_64*)pVGA_MEMORY; i < (uint_64*)(pVGA_MEMORY + 4000); i++){
    *i = value;
  }
  poutb(0x3D4, 0x0F);
  poutb(0x3D5, (uint_8)(0 & 0xFF));
  poutb(0x3D4, 0x0E);
  poutb(0x3D5, (uint_8)((0 >> 8) & 0xFF));
  pPrintString("Non critical System Error occured.\n\n", 0x0F | 0x90);
  pPrintString("Details:\n", 0x0F | 0x90);
  pPrintString(msg, 0x0F | 0x90);
  pPrintString("\n\n", 0x0F | 0x90);
  //CursorPosition = pCursorPosition;
}