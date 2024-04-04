#pragma once

#include "../Kernel.h"

bool Shell_LeftShiftPressed = false;
bool Shell_RightShiftPressed = false;
char Shell_commandBuffer[512];
uint_16 Shell_bufferSize;

void initShell(){
    Shell_bufferSize = 0;
    for(int i=0; i<512; i++) Shell_commandBuffer[i] = 0;
}

void RunShell(){
    PrintString("jOS> ");
}

void ParseCommand(){
    char arguments[16][64];
    uint_16 index;
    uint_16 index2;
    uint_8 args;

    for(int i=0; i<Shell_bufferSize; i++){
        if(Shell_commandBuffer[index] == ' '){ args++; index++; index2 = 0; }
        arguments[args][index2] = Shell_commandBuffer[index];
        index++;
        index2++;
    }

    if(strcmp(arguments[0], "shutdown")) shutdown();
    if(strcmp(arguments[0], "echo")) { for(int i=1; i<15; i++) { PrintString(arguments[i]); PrintChar(' '); } PrintString("\n"); }
    if(strcmp(arguments[0], "clear")) ClearScreen();
    if(strcmp(arguments[0], "help")) PrintString(HelpText);
    if(strcmp(arguments[0], "cmd") || strcmp(arguments[0], "commands")) PrintString(CommandsText);
    if(strcmp(arguments[0], "license")) PrintString(LicenseText);

    /* DEBUG */
    if(strcmp(arguments[0], "dprintmem")){
        MemoryMapEntry** UsableMemory = GetUsableMemoryRegions();
	    for(uint_8 i = 0; i < UsableMemoryRegionsCount; i++){
		    MemoryMapEntry* memMap = UsableMemoryMaps[i];
		    PrintMemoryMap(memMap);
	    }
    }

    Shell_bufferSize = 0;
    memset(arguments, 0, sizeof(arguments));
}

void Shell_KeyPress(uint_8 scanCode, uint_8 chr){
    if (chr != 0) {
		switch (Shell_LeftShiftPressed | Shell_RightShiftPressed)
		{
		case true:
			Shell_commandBuffer[Shell_bufferSize] = chr;
            Shell_bufferSize++;
            PrintChar(chr - 32);
			break;
		case false:
			Shell_commandBuffer[Shell_bufferSize] = chr;
            Shell_bufferSize++;
            PrintChar(chr);
			break;
		}

	}
	else {
		switch (scanCode) {
		case 0x8E: //Backspace
			if(Shell_bufferSize > 0){
                Shell_commandBuffer[Shell_bufferSize-1] = 0;
                Shell_bufferSize--;
                SetCursorPosition(CursorPosition-1);
                PrintChar(' ');
                SetCursorPosition(CursorPosition-1);
                //PrintString(IntegerToString(shell.bufferSize));
            }
			break;
		case 0x2A: //Left Shift
			Shell_LeftShiftPressed = true;
			break;
		case 0xAA: //Left Shift Released
			Shell_LeftShiftPressed = false;
		case 0x36: //Right Shift
			Shell_RightShiftPressed = true;
			break;
		case 0xB6: //Right Shift Released
			Shell_RightShiftPressed = false;
			break;
		case 0x9C: //Enter
			PrintString("\n");
            ParseCommand();
            RunShell();
			break;
		}
	}
}