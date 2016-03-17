#include <3ds.h>
#include <gfx_info.h>
#include "menugfx.h"


void draw_main_menu_bg(SudokuGFX s_gfx, gfxScreen_t screen) {
	
	if (s_gfx->top_frame % 3 == 0 && screen == GFX_TOP) s_gfx->bg_count++;
	
	int screen_h;
	
	if (GFX_TOP == screen) {
		screen_h = TOP_H;
	} else {
		screen_h = BOTTOM_H;
	}
	int frame = s_gfx->bg_count;
	//int frame = s_gfx->frame;
	
	//Draws two bg objects that are joined. This is to make it look like its continiously looping.
	int bg1_xpos1 = 0 + (frame % 240 ); //80 GCD of TOP_W and BOT_W
	int bg1_xpos2 = bg1_xpos1 - screen_h; //
	sf2d_draw_texture(s_gfx->main_menu_bg, 0, bg1_xpos1);
	
	sf2d_draw_texture(s_gfx->main_menu_bg, 0, bg1_xpos2);
	int bg2_xpos1 = 0 + (frame % 240); //80 GCD of TOP_W and BOT_W
	int bg2_xpos2 = bg2_xpos1 - screen_h; //
	sf2d_draw_texture(s_gfx->main_menu_bg, 0,  bg2_xpos1);
	sf2d_draw_texture(s_gfx->main_menu_bg, 0,  bg2_xpos2);
	
	sf2d_draw_rectangle(0, 0, TOP_W, TOP_H, RGBA8(0xFF, 0xFF, 0xFF, 0xBB));
}

void draw_main_menu_logo(SudokuGFX s_gfx) {
	sf2d_draw_rectangle(0, 97, TOP_W, 40, RGBA8(0xFF, 0x97, 0x89, 0xFF)); //bar
	sf2d_draw_texture(s_gfx->icon, 345, 93); //icon
	sf2d_draw_texture(s_gfx->text_sudoku3ds, 268, 124); //text
}

void draw_main_menu_difficulty(SudokuGFX s_gfx, int percentage) {
	sf2d_draw_rectangle(0, 120, TOP_W, 10, RGBA8(0xFF, 0x97, 0x89, 0xFF));
	sf2d_draw_texture(s_gfx->main_menu_difficulty, 0,  120);
	sf2d_draw_rectangle(279-(percentage*2), 119,3, 12, RGBA8(0x00, 0x00, 0x00, 0xFB)); //pos of box
}