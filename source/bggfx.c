#include <3ds.h>

#include "bggfx.h"

void draw_slide_background(SudokuGFX s_gfx, gfxScreen_t screen) {
	if (s_gfx->top_frame % 3 == 0 && screen == GFX_TOP) s_gfx->bg_count++;
	int screen_w;
	if (GFX_TOP == screen) {
		screen_w = TOP_W;
	} else {
		screen_w = BOTTOM_W;
	}
	int frame = s_gfx->bg_count;
	//int frame = s_gfx->frame;
	
	//Draws two bg objects that are joined. This is to make it look like its continiously looping.
	int bg1_xpos1 = 0 + (frame % 80); //80 GCD of TOP_W and BOT_W
	int bg1_xpos2 = bg1_xpos1 - screen_w; //
	sf2d_draw_texture(s_gfx->bg1, bg1_xpos1, 0);
	sf2d_draw_texture(s_gfx->bg1, bg1_xpos2, 0);
	int bg2_xpos1 = 0 + (frame % 80); //80 GCD of TOP_W and BOT_W
	int bg2_xpos2 = bg2_xpos1 - screen_w; //
	sf2d_draw_texture(s_gfx->bg2, bg2_xpos1, 0);
	sf2d_draw_texture(s_gfx->bg2, bg2_xpos2, 0);
	
}


 


void draw_top_background(SudokuGFX s_gfx) {
	sf2d_draw_rectangle(0, 0, TOP_W, TOP_H, RGBA8(0xF2, 0xF2, 0xF2, 0xFF));  //draw plain bg
	draw_slide_background(s_gfx, GFX_TOP);
	sf2d_draw_rectangle(0, 0, TOP_W, TOP_H, RGBA8(0xF2, 0xF2, 0xF2, 0x83)); //dampen
	
	sf2d_draw_rectangle(0, 5, TOP_W, 38, RGBA8(0xE9, 0x6E, 0x9C, 0xFF)); //draw status bar
	sf2d_draw_texture(s_gfx->icon, 22, 0); //Icon
	sf2d_draw_texture(s_gfx->text_sudoku3ds, 80, 28); //text sudoku3ds

}



extern void draw_bottom_background(SudokuGFX s_gfx) {
	sf2d_draw_rectangle(0, 0, BOTTOM_W, TOP_H, RGBA8(0xF2, 0xF2, 0xF2, 0xFF)); //plain bg
	draw_slide_background(s_gfx, GFX_BOTTOM);

	sf2d_draw_rectangle(0, 0, BOTTOM_W, TOP_H, RGBA8(0xF2, 0xF2, 0xF2, 0x93));  //dampen bg
	
	sf2d_draw_rectangle(0, -10, BOTTOM_W, 20, RGBA8(0xFA, 0xAA, 0xA3, 0x93)); //peach
	sf2d_draw_rectangle(0, 30, BOTTOM_W, 20, RGBA8(0x8E, 0xCF, 0xB2, 0x93)); //green
	sf2d_draw_rectangle(0, 70, BOTTOM_W, 20, RGBA8(0xE5, 0xCD, 0x7C, 0x93)); //yellow
	sf2d_draw_rectangle(0, 110, BOTTOM_W, 20, RGBA8(0x7B, 0xD3, 0xEA, 0x93)); //blue
	sf2d_draw_rectangle(0, 150, BOTTOM_W, 20, RGBA8(0xC3, 0xA7, 0xE0, 0x93)); //purple
	sf2d_draw_rectangle(0, 190, BOTTOM_W, 20, RGBA8(0xD7, 0x9B, 0xB5, 0x93)); //pink
	sf2d_draw_rectangle(0, 230, BOTTOM_W, 20, RGBA8(0xFA, 0xAA, 0xA3, 0x93)); //peach
	

}
