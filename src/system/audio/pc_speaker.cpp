#pragma once

#include "../../Kernel.h"

void PCSpeaker_PlaySound(uint_32 nFrequence) {
 	uint_32 Div;
 	uint_8 tmp;

 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint_8) (Div) );
 	outb(0x42, (uint_8) (Div >> 8));
 
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
}

void PCSpeaker_ShutUp() {
 	uint_8 tmp = inb(0x61) & 0xFC;
 	outb(0x61, tmp);
}

 void PCSpeaker_Beep(uint_32 nFrequence, uint_32 seconds) {
 	 PCSpeaker_PlaySound(nFrequence);
 	 FakePIT_WaitSeconds(seconds);
 	 PCSpeaker_ShutUp();
 }