#include "Kernel.h"

extern const char Logo[];
extern const char HelpText[];
extern const char LicenseText[];
extern const char CommandsText[];
extern const char BackgroundASCII[];
extern const char KPanicASCII[];

int K_OS_State = 0;

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

void startup(){
	ClearScreen();
	PrintString("== J Operating System ==\n\n");
	PrintString("F1 - Cancel & Shutdown\n");
	PrintString("F2 - Enter Shell (Normal Mode)\n");
	PrintString("F3 - Enter Shell (Graphics Mode)\n");
	PrintString("F4 - Enter Graphics Mode\n\n");
	PrintString("F6 - Start Shell (Safe Mode)\n");
	PrintString("F7 - Start Fallback Shell\n");
	PrintString("F8 - Start Setup\n");
	SetCursorPosition(VGA_HEIGHT*VGA_WIDTH);
}

void startup_key(unsigned char scanCode, unsigned char chr){
	if (chr == 0) {
        switch (scanCode) {
			case 0x3B: // F1
				shutdown();
				break;
			case 0x3C: // F2
				Shell_Clear();
				Shell_Output(Logo);
				Shell_Run();
				read_rtc();
				K_OS_State = 2;
			case 0x3D: // F3
				ClearScreen();
				PrintString("Under development.");
				for(;;) asm("hlt");
			case 0x3E: // F4
				ClearScreen();
				PrintString("Under development.");
				for(;;) asm("hlt");
			case 0x40: // F6
				ClearScreen();
				PrintString("Under development.");
				for(;;) asm("hlt");
			case 0x41: // F7
				ClearScreen();
				PrintString("Under development.");
				for(;;) asm("hlt");
			case 0x42: // F8
				ClearScreen();
				PrintString("Under development.");
				for(;;) asm("hlt");
			case 0x9C: //Enter
				Shell_Clear();
				Shell_Output(Logo);
				Shell_Run();
				read_rtc();
				K_OS_State = 2;
		}
	}
}

extern "C" void _start(){
	init();
	PrintString("Starting J Operating System...");
	PCSpeaker_Beep(500, 1); ClearScreen();
	startup();
	uint_8 tmp = second;
	uint_8 tmp2 = minute;
	while(true){ // main kernel loop
		if(K_OS_State > 1){
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
	}
	return;
}
