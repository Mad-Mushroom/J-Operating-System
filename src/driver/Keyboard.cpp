#pragma once

#include "../Kernel.h"
#include "../shell/shell.cpp"

uint_8 LastScancode;

void KeyboardHandler(uint_8 scanCode, uint_8 chr) {

	switch (LastScancode) {
	case 0xE0:
		//Shell_KeyPress0xE0(scanCode);
		break;
	default:
		Shell_KeyPress(scanCode, chr);
	}

	LastScancode = scanCode;
}