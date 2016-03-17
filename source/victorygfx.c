#include <3ds.h>
#include"victorygfx.h"

//Handles victory drawing
void draw_victory(SudokuGFX s_gfx, gfxScreen_t screen) {
	if (screen == GFX_TOP) {
		sf2d_draw_texture(s_gfx->victory, 40-(TOP_W * 2) + s_gfx->victory_frame, -35);
		
	} else {
		//sf2d_draw_texture(s_gfx->victory, -(BOTTOM_W * 2) - 195 + s_gfx->victory_frame, 0);
		sf2d_draw_texture(s_gfx->victory, -(TOP_W * 2)-40 + s_gfx->victory_frame, -35);
	}
}

