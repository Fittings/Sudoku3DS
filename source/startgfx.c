#include <stdlib.h> //malloc

#include <3ds.h>
#include <math.h> //sqrt


#include "startgfx.h"
#include "sudoku.h" //ZZZ might not need this



void draw_start_gfx_top(SudokuGFX s_gfx) {
	sf2d_draw_rectangle(0, 0, TOP_W, TOP_H, RGBA8(0x00, 0x00, 0x00, 0x88));  //dampen bg
	//draw a transparent rectangle or something in the centre
	//draw icons for reset, main menu, exit
}

void draw_start_gfx_bottom(SudokuGFX s_gfx) {
	sf2d_draw_rectangle(0, 0, BOTTOM_W, BOTTOM_H, RGBA8(0x00, 0x00, 0x00, 0x88));  //dampen bg
}

