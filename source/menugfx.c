#include <3ds.h>
#include <gfx_info.h>

#include "menugfx.h"


void draw_main_menu(SudokuGFX s_gfx, int percentage, gfxScreen_t screen) {
	if (s_gfx->top_frame % 2 == 0 && screen == GFX_TOP) s_gfx->bg_count++;
	
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
	if (screen == GFX_TOP) {
		sf2d_draw_rectangle(0, 95, TOP_W, 50, RGBA8(0xE9, 0x6E, 0x9C, 0xFF));
		sf2d_draw_texture(s_gfx->icon, 175, 95);
	}
	
	
	
}