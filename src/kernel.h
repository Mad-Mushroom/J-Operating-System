#pragma once

void shutdown();

extern const char Logo[];
extern const char HelpText[];
extern const char LicenseText[];
extern const char CommandsText[];
extern const char BackgroundASCII[];

#define OS_VERSION "J Operating System Alpha [v0.1.0]"

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

/* Driver */
#include "driver/VGA_Screen.cpp"
#include "driver/Keyboard.cpp"

/* Shell */
#include "shell/shell.cpp"
