#pragma once

#include "../Kernel.h"

#define SHELL_VERSION "jShell [v0.2.7]"

bool Shell_LeftShiftPressed = false;
bool Shell_RightShiftPressed = false;
char Shell_commandBuffer[512];
uint_16 Shell_bufferSize;
uint_16 Shell_CursorPosition;

void Shell_Init(){
    Shell_bufferSize = 0;
    for(int i=0; i<512; i++) Shell_commandBuffer[i] = 0;
    Shell_CursorPosition = VGA_WIDTH;
}

void Shell_Run(){
    SetCursorPosition((VGA_HEIGHT - 1) * VGA_WIDTH);
    PrintString("jOS>                                                                            ", BACKGROUND_LIGHTGRAY | FOREGROUND_BLUE);
    SetCursorPosition(((VGA_HEIGHT - 1) * VGA_WIDTH) + 5);
}

void Shell_Output(const char* str, uint_8 color = DEFAULT_BACKGROUND | DEFAULT_FOREGROUND){
    uint_16 oCursorPosition = CursorPosition;
    SetCursorPosition(Shell_CursorPosition);
    PrintString(str, color);
    Shell_CursorPosition = CursorPosition;
    SetCursorPosition(oCursorPosition);
}

void Shell_DrawBackground(){
    uint_16 oCursorPosition = CursorPosition;
    SetCursorPosition(0);
    PrintString(BackgroundASCII, BACKGROUND_BLACK | FOREGROUND_DARKGRAY);
    SetCursorPosition(oCursorPosition);
}

void Shell_UpdateTitleBar(){
    uint_16 oCursorPosition = CursorPosition;
    SetCursorPosition(0);
    PrintString(OS_VERSION, BACKGROUND_BLUE | FOREGROUND_YELLOW);
    PrintString("                                      ", BACKGROUND_BLUE | FOREGROUND_YELLOW);
    read_rtc();
    PrintString(IntegerToString(hour), BACKGROUND_BLUE | FOREGROUND_YELLOW); PrintString(":", BACKGROUND_BLUE | FOREGROUND_YELLOW); PrintString(IntegerToString(minute), BACKGROUND_BLUE | FOREGROUND_YELLOW);
    SetCursorPosition(oCursorPosition);
}

void Shell_Clear(){
    ClearScreen();
    Shell_CursorPosition = VGA_WIDTH;
    Shell_DrawBackground();
    Shell_UpdateTitleBar();
}

void Shell_ParseCommand(){
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

    if(strcmp(arguments[0], "shutdown")){
        shutdown();
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "echo")){
        for(int i=1; i<15; i++){
            Shell_Output(arguments[i]);
            Shell_Output(" ");
        }
        //PrintString("\n");
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "clear")){
        Shell_Clear();
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "help")){
        Shell_Output(HelpText);
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "cmd") || strcmp(arguments[0], "commands")){
        Shell_Output(CommandsText);
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "ucmd")){
        Shell_Output("jOS (undocumented) Commands\n");
        Shell_Output("---------------------------\n\n");
        Shell_Output("start - display start screen\n");
        Shell_Output("dpmem - output memory information\n");
        Shell_Output("dpanic - trigger kernel panic\n");
        Shell_Output("derr - trigger non-critical system error\n");
        Shell_Output("ucmd - display this\n");
        Shell_Output("dlastcmos - display last time read from rtc\n");
        Shell_Output("sound - plays sound on pc speaker (1st argument = frequency)\n");
        Shell_Output("stopsound - stops the sound\n");
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "sound")){
        PCSpeaker_PlaySound(stringToInt(arguments[1]));
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "stopsound") || strcmp(arguments[0], "ss")){
        PCSpeaker_ShutUp();
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "license")){
        Shell_Output(LicenseText);
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "info") || strcmp(arguments[0], "neofetch")){
        read_rtc();
        Shell_Output("\n");
        Shell_Output("            /$$$$$$   /$$$$$$     "); Shell_Output("OS: The J Operating System"); Shell_Output("\n");
        Shell_Output("           /$$__  $$ /$$__  $$    "); Shell_Output("Kernel: jKern - jOS"); Shell_Output("\n");
        Shell_Output("       /$$| $$  \\ $$| $$  \\__/    "); Shell_Output("Version: "); Shell_Output(OS_VERSION);
        Shell_Output("      |__/| $$  | $$|  $$$$$$     "); Shell_Output("Build Date: "); Shell_Output(OS_BUILD_DATE); Shell_Output("\n");
        Shell_Output("       /$$| $$  | $$ \\____  $$    "); Shell_Output("Memory: "); Shell_Output(IntegerToString(TotalMemoryLength / 1000)); Shell_Output("k / "); Shell_Output(IntegerToString(TotalMemoryLength / 1000000)); Shell_Output("M"); Shell_Output("\n");
        Shell_Output("      | $$| $$  | $$ /$$  \\ $$    "); Shell_Output("Uptime: "); if(OS_UPTIME < 60){Shell_Output(IntegerToString(OS_UPTIME));Shell_Output("s");} if(OS_UPTIME > 60){Shell_Output(IntegerToString(OS_UPTIME / 60));Shell_Output("m ");Shell_Output(IntegerToString(OS_UPTIME));Shell_Output("s");} Shell_Output("\n");
        Shell_Output("      | $$|  $$$$$$/|  $$$$$$/    "); Shell_Output("CMOS Time: "); Shell_Output(IntegerToString(month)); Shell_Output("/"); Shell_Output(IntegerToString(day)); Shell_Output("/"); Shell_Output(IntegerToString(year)); Shell_Output(" "); Shell_Output(IntegerToString(hour)); Shell_Output(":"); Shell_Output(IntegerToString(minute)); Shell_Output(":"); Shell_Output(IntegerToString(second)); Shell_Output("\n");
        Shell_Output("      | $$ \\______/  \\______/     "); Shell_Output("Shell: "); Shell_Output(SHELL_VERSION); Shell_Output("\n");
        Shell_Output(" /$$  | $$                        "); Shell_Output("Resolution: "); Shell_Output(IntegerToString(VGA_WIDTH)); Shell_Output("x"); Shell_Output(IntegerToString(VGA_HEIGHT)); Shell_Output(""); Shell_Output("\n");
        Shell_Output("|  $$$$$$/                        "); Shell_Output("  ", 0x00 | BACKGROUND_BLACK);Shell_Output("  ", 0x00 | BACKGROUND_BLUE);Shell_Output("  ", 0x00 | BACKGROUND_GREEN);Shell_Output("  ", 0x00 | BACKGROUND_CYAN);Shell_Output("  ", 0x00 | BACKGROUND_RED);Shell_Output("  ", 0x00 | BACKGROUND_MAGENTA);Shell_Output("  ", 0x00 | BACKGROUND_BROWN);Shell_Output("  ", 0x00 | BACKGROUND_LIGHTGRAY);Shell_Output("\n");
        Shell_Output(" \\______/                         "); Shell_Output("  ", 0x00 | BACKGROUND_BLINKINGBLACK);Shell_Output("  ", 0x00 | BACKGROUND_BLINKINGBLUE);Shell_Output("  ", 0x00 | BACKGROUND_BLINKINGGREEN);Shell_Output("  ", 0x00 | BACKGROUND_BLINKINGCYAN);Shell_Output("  ", 0x00 | BACKGROUND_BLINKINGRED);Shell_Output("  ", 0x00 | BACKGROUND_BLINKINGMAGENTA);Shell_Output("  ", 0x00 | BACKGROUND_BLINKINGYELLOW);Shell_Output("  ", 0x00 | BACKGROUND_BLINKINGWHITE);
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "start")){
        Shell_Output(Logo);
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "time")){
        read_rtc();
        Shell_Output(IntegerToString(month)); Shell_Output("/"); Shell_Output(IntegerToString(day)); Shell_Output("/"); Shell_Output(IntegerToString(year)); Shell_Output(" "); Shell_Output(IntegerToString(hour)); Shell_Output(":"); Shell_Output(IntegerToString(minute)); Shell_Output(":"); Shell_Output(IntegerToString(second));
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
    }

    /* DEBUG */
    if(strcmp(arguments[0], "dpmem")){
        Shell_Output("Memory Regions: "); Shell_Output(IntegerToString(MemoryRegionCount)); Shell_Output("\n");
        //Shell_Output("Usable Memory Regions: "); Shell_Output(IntegerToString(UsableMemoryRegionsCount)); Shell_Output("\n");
        Shell_Output("\n");
        MemoryMapEntry** UsableMemory = GetUsableMemoryRegions();
	    for(uint_8 i = 0; i < UsableMemoryRegionsCount; i++){
		    MemoryMapEntry* memMap = UsableMemoryMaps[i];
		    Shell_Output("Memory Base: "); Shell_Output(IntegerToString(memMap->BaseAddress)); Shell_Output("\n");
            Shell_Output("Region Length: "); Shell_Output(IntegerToString(memMap->RegionLength)); Shell_Output("\n");
            Shell_Output("Memory Type: "); Shell_Output(IntegerToString(memMap->RegionType)); Shell_Output("\n");
            Shell_Output("Memory Attributes: "); Shell_Output(IntegerToString(memMap->ExtendedAttributes)); Shell_Output("\n");
	    }
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        Shell_Output("\n"); Shell_Output("Memory: "); Shell_Output(IntegerToString(TotalMemoryLength));
        Shell_Output("\n"); Shell_Output("Memory: "); Shell_Output(IntegerToString(TotalMemoryLength / 1000)); Shell_Output("k");
        Shell_Output("\n"); Shell_Output("Memory: "); Shell_Output(IntegerToString(TotalMemoryLength / 1000000)); Shell_Output("M");
        return;
    }
    if(strcmp(arguments[0], "dpanic")){
        kpanic("DEBUGGING.\n\nUser-triggered Kernel Panic, no real Error :)\nBut how do you know about this command?");
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "derr")){
        ncErr("DEBUGGING.\n\nUser-triggered Error, no real Error :)\nBut how do you know about this command?");
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "dlastcmos")){
        Shell_Output(IntegerToString(month)); Shell_Output("/"); Shell_Output(IntegerToString(day)); Shell_Output("/"); Shell_Output(IntegerToString(year)); Shell_Output(" "); Shell_Output(IntegerToString(hour)); Shell_Output(":"); Shell_Output(IntegerToString(minute)); Shell_Output(":"); Shell_Output(IntegerToString(second));
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }
    if(strcmp(arguments[0], "thermo")){
        Shell_Output("1. Thermodynamisches Gesetz:\n\nEnergie kann weder Uebertragen, noch umgewandelt werden. Sie wird entweder erzeugt, oder vernichtet.");
        Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
        return;
    }

    if(Shell_bufferSize != 0) Shell_Output("Command or Binary not recognized!\n");
    Shell_bufferSize = 0; memset(arguments, 0, sizeof(arguments));
    return;
}

void Shell_KeyPress(uint_8 scanCode, uint_8 chr){
    if (chr == 0) {
        switch (scanCode) {
		case 0x8E: //Backspace
			if(Shell_bufferSize > 0){
                Shell_commandBuffer[Shell_bufferSize-1] = 0;
                Shell_bufferSize--;
                SetCursorPosition(CursorPosition-1);
                PrintChar(' ', BACKGROUND_LIGHTGRAY | FOREGROUND_BLUE);
                SetCursorPosition(CursorPosition-1);
            }
			break;
		case 0x2A: //Left Shift
			Shell_LeftShiftPressed = true;
			break;
		case 0xAA: //Left Shift Released
			Shell_LeftShiftPressed = false;
            break;
		case 0x36: //Right Shift
			Shell_RightShiftPressed = true;
			break;
		case 0xB6: //Right Shift Released
			Shell_RightShiftPressed = false;
			break;
		case 0x9C: //Enter
			//PrintString("\n");
            Shell_Clear();
            Shell_ParseCommand();
            Shell_Run();
			break;
		}
	}
	else {
		switch (Shell_LeftShiftPressed | Shell_RightShiftPressed)
		{
		case true:
			Shell_commandBuffer[Shell_bufferSize] = chr - 32;
            Shell_bufferSize++;
            PrintChar(chr - 32, BACKGROUND_LIGHTGRAY | FOREGROUND_BLUE);
			break;
		case false:
			Shell_commandBuffer[Shell_bufferSize] = chr;
            Shell_bufferSize++;
            PrintChar(chr, BACKGROUND_LIGHTGRAY | FOREGROUND_BLUE);
			break;
		}
	}
}