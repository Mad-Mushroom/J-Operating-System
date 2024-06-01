#pragma once

void shutdown();
void startup_key(unsigned char scanCode, unsigned char chr);

extern const char Logo[];
extern const char HelpText[];
extern const char LicenseText[];
extern const char CommandsText[];
extern const char BackgroundASCII[];
extern const char KPanicASCII[];
extern int K_OS_State;

#define OS_DEBUG 0
#define OS_VERSION "J Operating System Alpha [v0.1.0]    " // always 36 chars long!
#define OS_VERSION_SHORT "Alpha [v0.1.0]"
#define OS_BUILD_DATE "Sat, Apr 9. 2024"

/* Misc */
#include "misc/KBScanCodeSet1.h"
#include "misc/TextModeColorCodes.h"
#include "misc/Typedefs.h"
#include "misc/usefulFuncs.h"

/* System */
#include "system/panic.cpp"
#include "system/IO.cpp"
#include "system/IDT.cpp"
#include "system/memory/MemoryMap.cpp"
#include "system/memory/memory.cpp"
#include "system/memory/heap.cpp"
#include "system/timing/cmos.cpp"
//#include "system/timing/pit.cpp"
#include "system/audio/pc_speaker.cpp"

/* Driver */
#include "driver/VGA_Screen.cpp"
#include "driver/Keyboard.cpp"

/* Shell */
#include "jShell/shell.cpp"
