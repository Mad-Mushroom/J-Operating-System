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
	//PrintString("Starting J Operating System...\n", BACKGROUND_BLACK | FOREGROUND_WHITE);
	InitializeIDT();
	if(OS_DEBUG == 1) PrintString("\nInitialized IDT.");
	MainKeyboardHandler = KeyboardHandler;
	if(OS_DEBUG == 1) PrintString("\nInitialized Keyboard Handler.");
	InitializeHeap(0x100000, 0x100000);
	GetUsableMemoryRegions();
	if(OS_DEBUG == 1) PrintString("Initialized Heap.");
	Shell_Init();
	if(OS_DEBUG == 1) PrintString("\nInitialized Shell.");
	read_rtc();
	if(OS_DEBUG == 1) PrintString("\nInitialized CMOS.");
	if(OS_DEBUG == 1) PrintString("\nDone Initializing.\n\n");
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

extern "C" void _start(){
	init();
	PrintString("Starting J Operating System...");
	PCSpeaker_Beep(500, 1); ClearScreen();
	if(OS_DEBUG == 0){
		Shell_Clear();
		Shell_Output(Logo);
	}
	Shell_Run();
	read_rtc();
	uint_8 tmp = second;
	uint_8 tmp2 = minute;
	while(true){ // main kernel loop
		read_rtc();
        if(second == tmp + 1){
            tmp = second;
            OS_UPTIME++;
        }
		if(minute == tmp2 + 1){
			tmp2 = minute;
			Shell_UpdateTitleBar();
		}
	}
	return;
}
