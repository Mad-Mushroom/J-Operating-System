#pragma once

#include "../Kernel.h"
#include "../jShell/shell.cpp"

uint_8 LastScancode;

void KeyboardHandler(uint_8 scanCode, uint_8 chr) {

	switch (LastScancode) {
	case 0xE0:
		//Shell_KeyPress0xE0(scanCode);
		break;
	default:
		if(K_OS_State == 0) startup_key(scanCode, chr);
		if(K_OS_State == 2) Shell_KeyPress(scanCode, chr);
	}

	LastScancode = scanCode;
}