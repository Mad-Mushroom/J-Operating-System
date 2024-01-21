#pragma once

#include "../kernel.h"

uint_8 selection;

void U_MainMenu(){
	D_PrintChar(205);
	D_Locate((D_VGA_WIDTH-25)/2, 4, test, M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 5, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 6, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 7, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 8, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 9, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 10, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 11, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 12, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 13, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 14, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 15, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 16, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 17, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 18, "|                      |", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
	D_Locate((D_VGA_WIDTH-25)/2, 19, "========================", M_BACKGROUND_BLUE | M_FOREGROUND_WHITE);
}