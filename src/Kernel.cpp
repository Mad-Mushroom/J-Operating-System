#include "Kernel.h"

extern const char Logo[];
extern const char HelpText[];
extern const char LicenseText[];
extern const char CommandsText[];
extern const char BackgroundASCII[];
extern const char KPanicASCII[];

void init(){
	ClearScreen(BACKGROUND_BLACK | FOREGROUND_WHITE);
	SetCursorPosition(0);
	PrintString("Starting J Operating System...\n", BACKGROUND_BLACK | FOREGROUND_WHITE);
	InitializeIDT();
	PrintString("\nInitialized IDT.");
	MainKeyboardHandler = KeyboardHandler;
	PrintString("\nInitialized Keyboard Handler.");
	//InitializeHeap(0x100000, 0x100000);
	PrintString("Initialized Heap.");
	initShell();
	PrintString("\nInitialized Shell.");
	PrintString("\nDone Initializing.\n\n");
}

void StartScreen(){
	ClearScreen();
	Shell_DrawBackground();
	PrintString(Logo);
	PrintString(OS_VERSION);
	PrintString("\nCopyright (c) 2024 MadMushroom\n\n");
    //PrintString("\n----------------------------------------\n");
}

void shutdown(){
	ClearScreen(BACKGROUND_BLACK | FOREGROUND_YELLOW);
	SetCursorPosition(PositionFromCoords(VGA_WIDTH/2-(40/2)-1, VGA_HEIGHT/2));
	PrintString("It's now safe to turn off your computer.", BACKGROUND_BLACK | FOREGROUND_YELLOW); // 40
	SetCursorPosition(PositionFromCoords(VGA_WIDTH/2-(14/2)-1, VGA_HEIGHT-1));
	PrintString("System halted.", BACKGROUND_BLACK | FOREGROUND_RED);
	SetCursorPosition(VGA_HEIGHT * VGA_WIDTH);
	while(true) asm("hlt");
}

extern "C" void _start() {
	init();
	StartScreen();
	RunShell();
	return;
}
