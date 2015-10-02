#include <stdlib.h> //malloc

#include <3ds.h>
#include <math.h> //sqrt


#include "startgfx.h"
#include "sudoku.h" //ZZZ might not need this



void draw_start_gfx_top(SudokuGFX s_gfx, int cursor) {
	sf2d_draw_rectangle(0, 0, TOP_W, TOP_H, RGBA8(0x00, 0x00, 0x00, 0x88));  //dampen bg
	//sf2d_draw_rectangle(65, 80, 270, 80, RGBA8(0x33, 0x7A, 0x87, 0xFF)); //temp background image. See refs for ideal start menu
	//sf2d_draw_fill_circle(85, 100 + (cursor * 20), 5,  RGBA8(0xFF, 0xFF, 0xFF, 0xFF));
	
	//sf2d_draw_rectangle(65, 80, 270, 80, RGBA8(0x33, 0x7A, 0x87, 0xFF));
	sf2d_draw_texture(s_gfx->start_menu, 65, 80);
	sf2d_draw_texture(s_gfx->start_selector, 94, 92+(cursor*20));
	//text
	sf2d_draw_texture(s_gfx->text_reset, 140, 90); //RESET PUZZLE
	sf2d_draw_texture(s_gfx->text_main_menu, 140, 110); //MAIN MENU
	sf2d_draw_texture(s_gfx->text_quit_game, 140, 132); //QUIT GAME

	//draw a transparent rectangle or something in the centre
	//draw icons for reset, main menu, exit
}

void draw_start_gfx_bottom(SudokuGFX s_gfx) {
	sf2d_draw_rectangle(0, 0, BOTTOM_W, BOTTOM_H, RGBA8(0x00, 0x00, 0x00, 0x88));  //dampen bg
}

