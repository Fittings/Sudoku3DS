#include <3ds.h>
#include <gfx_info.h>

#include "menugfx.h"


extern void draw_main_menu(SudokuGFX s_gfx, int percentage) {
	sf2d_draw_rectangle(percentage,  70, 50, 50, RGBA8(0xE9, 0xFF, 0xFF, 0xFF)); //draw status bar
}