#include <3ds.h>
#include"victorygfx.h"

void draw_stars() {


}

//Handles victory drawing
void draw_victory(SudokuGFX s_gfx) {
	if (s_gfx->victory_frame < 15) {
		//pop out text
	}
	sf2d_draw_fill_circle(200, 120, 32, RGBA8(0x00, 0x00, 0x00, 0xFF)); //peach circle
	sf2d_draw_fill_circle(200, 120, 30, RGBA8(0xFA, 0xAA, 0xA3, 0x93)); //peach circle
}

