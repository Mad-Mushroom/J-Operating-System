#pragma once

#include "../Kernel.h"

bool LeftShiftPressed = false;
bool RightShiftPressed = false;

class Shell {
    public:
        const char* Username;
        char commandBuffer[512];
        uint_16 bufferSize;
};
Shell shell;

void initShell(){
    shell.Username = "jOS";
    shell.bufferSize = 0;
    for(int i=0; i<512; i++) shell.commandBuffer[i] = 0;
}

void RunShell(){
    PrintString(shell.Username);
    PrintString("> ");
}

void ParseCommand(){
    char arguments[16][64];
    uint_16 index;
    uint_16 index2;
    uint_8 args;

    for(int i=0; i<shell.bufferSize; i++){
        if(shell.commandBuffer[index] == ' '){ args++; index++; index2 = 0; }
        arguments[args][index2] = shell.commandBuffer[index];
        index++;
        index2++;
    }

    if(strcmp(arguments[0], "shutdown")) shutdown();
    if(strcmp(arguments[0], "echo")) { for(int i=1; i<15; i++) { PrintString(arguments[i]); PrintChar(' '); } PrintString("\n"); }

    shell.bufferSize = 0;
    memset(arguments, 0, sizeof(arguments));
}

void Shell_EnterPressed(){
    PrintString("\n");
    ParseCommand();
    RunShell();
}

void Shell_AddChar(char chr){
    shell.commandBuffer[shell.bufferSize] = chr;
    shell.bufferSize++;
    PrintChar(chr);
}

void Shell_KeyPress(uint_8 scanCode, uint_8 chr){
    if (chr != 0) {
		switch (LeftShiftPressed | RightShiftPressed)
		{
		case true:
			shell.commandBuffer[shell.bufferSize] = chr;
            shell.bufferSize++;
            PrintChar(chr - 32);
			break;
		case false:
			shell.commandBuffer[shell.bufferSize] = chr;
            shell.bufferSize++;
            PrintChar(chr);
			break;
		}

	}
	else {
		switch (scanCode) {
		case 0x8E: //Backspace
			shell.commandBuffer[shell.bufferSize-1] = 0;
            shell.bufferSize--;
            SetCursorPosition(CursorPosition-1);
            PrintChar(' ');
            SetCursorPosition(CursorPosition-1);
			break;
		case 0x2A: //Left Shift
			LeftShiftPressed = true;
			break;
		case 0xAA: //Left Shift Released
			LeftShiftPressed = false;
		case 0x36: //Right Shift
			RightShiftPressed = true;
			break;
		case 0xB6: //Right Shift Released
			RightShiftPressed = false;
			break;
		case 0x9C: //Enter
			PrintString("\n");
            ParseCommand();
            RunShell();
			break;
		}
	}
}