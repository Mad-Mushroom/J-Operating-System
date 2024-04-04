#pragma once

#include "../Kernel.h"
#include "../shell/shell.cpp"

uint_8 LastScancode;

void StandardKeyboardHandler(uint_8 scanCode, uint_8 chr) {
	Shell_KeyPress(scanCode, chr);
}

void KeyboardHandler0xE0(uint_8 scanCode) {
	switch (scanCode)
	{
	case 0x50:
		//SetCursorPosition(CursorPosition + VGA_WIDTH);
		break;
	case 0x48:
		//Shell_UpPressed();
		//SetCursorPosition(CursorPosition - VGA_WIDTH);
		break;
	default:
		break;
	}

}
void KeyboardHandler(uint_8 scanCode, uint_8 chr) {

	switch (LastScancode) {
	case 0xE0:
		KeyboardHandler0xE0(scanCode);
		break;
	default:
		StandardKeyboardHandler(scanCode, chr);
	}

	LastScancode = scanCode;
}