#include <stdlib.h> //malloc

#include <3ds.h>
#include <math.h> //sqrt



#include "sudoku.h" //ZZZ might not need this
#include "mylib.h" //mod
#include "sudokugfx.h"
#include "startgfx.h" //Start menu graphics

#define BG_COL 40 //Need to remove these magic numbers and actually do the maths on this.
#define BG_ROW 75
#define BOX_SIZE 5


//Load Images

//Main Background
#include "bg1_bin.h"
#include "bg2_bin.h"
#include "icon_bin.h"
#include "text_sudoku3ds_bin.h"

//Sudoku
#include "immut_numbers_bin.h"
#include "mut_numbers_bin.h"
#include "selector_bin.h"

//Start Menu
#include "start_menu_bin.h"
#include "start_selector_bin.h"
#include "text_quit_game_bin.h"
#include "text_reset_bin.h"
#include "text_main_menu_bin.h"


/* This file is a struct dedicated to loading and keeping
 * control of variables needed by other graphics classes.
 * ZZZ I need to seperate all draws into another class
 */




SudokuGFX SudokuGFX_init() {
	sf2d_init();
	SudokuGFX my_gfx = malloc(sizeof *my_gfx);
	if (my_gfx == NULL) {
		free(my_gfx);
		return NULL;
	}
	my_gfx->bg_count = 0;
	my_gfx->top_frame = 0;
	my_gfx->bottom_frame = 0;
	
	//Load Main BG images
	my_gfx->bg1				= sfil_load_PNG_buffer(bg1_bin, SF2D_PLACE_RAM);
	my_gfx->bg2				= sfil_load_PNG_buffer(bg2_bin, SF2D_PLACE_RAM);
	my_gfx->text_sudoku3ds	= sfil_load_PNG_buffer(text_sudoku3ds_bin, SF2D_PLACE_RAM);
	my_gfx->icon			= sfil_load_PNG_buffer(icon_bin, SF2D_PLACE_RAM);
	
	//Load Sudoku Images
	my_gfx->immut_numbers 	= sfil_load_PNG_buffer(immut_numbers_bin, SF2D_PLACE_RAM);
	my_gfx->mut_numbers 	= sfil_load_PNG_buffer(mut_numbers_bin, SF2D_PLACE_RAM);
	my_gfx->selector		= sfil_load_PNG_buffer(selector_bin, SF2D_PLACE_RAM);
	
	//Load Start Menu images
	my_gfx->start_menu 		= sfil_load_PNG_buffer(start_menu_bin, SF2D_PLACE_RAM);
	my_gfx->start_selector	= sfil_load_PNG_buffer(start_selector_bin, SF2D_PLACE_RAM);
	my_gfx->text_quit_game 	= sfil_load_PNG_buffer(text_quit_game_bin, SF2D_PLACE_RAM);
	my_gfx->text_reset		= sfil_load_PNG_buffer(text_reset_bin, SF2D_PLACE_RAM);
	my_gfx->text_main_menu	= sfil_load_PNG_buffer(text_main_menu_bin, SF2D_PLACE_RAM);
	
	return my_gfx;
}

//Frees SudokuGFX
void sudoku_gfx_free(SudokuGFX s_gfx) {
	sf2d_fini();
	if (s_gfx != NULL) {
		free(s_gfx);
	}
}

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




//Handles victory drawing
void draw_victory(int victory_flag) {
	if (victory_flag) {
		sf2d_draw_rectangle(390, 230, 10, 10, RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //draw purp victory box
	} else {
		sf2d_draw_rectangle(390, 230, 10, 10, RGBA8(0xFF, 0xFF, 0xFF, 0xFF)); //draw white defeat box
	}
}

//ZZZ TILE_SIZE is a magic number, Fix this
//Needs to know, (size, s_gfx, sudoku_array, edit_array 
void draw_sudoku(SudokuGFX s_gfx, int *sudoku_array, int *edit_array, int size, int x_offset, int y_offset, int cursor) {
	int i, square = sqrt(size);
	int row=0, col=0, val=0;
	int x=0, y=0;// offset = 0;
	int x_div_offset = 0;
	int y_div_offset = 0;

	for (i=0; i < (size*size); i++) {
		row = i % size;
		col = i / size;
		x = row * TILE_SIZE; y = col * TILE_SIZE;
		if (row % (square) == 0) x_div_offset = (row-1)*1;
		if (col % (square) == 0) y_div_offset = (col-1)*1;
		x += (x_offset+x_div_offset); y += (y_offset+y_div_offset);
		val = sudoku_array[i];
		if (edit_array[i]) { //draw mutable block
			sf2d_draw_texture_part(s_gfx->mut_numbers, x, y, val*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
		} else { //else draw immutable block
			sf2d_draw_texture_part(s_gfx->immut_numbers, x, y, val*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
		}
		if (row == (cursor%size) && col == (cursor/size)) {//draw selector
			sf2d_draw_texture(s_gfx->selector, x, y);
		}
		row++;
	} 
}




//This should be called paired with end_draw()
void start_draw(SudokuGFX s_gfx, gfxScreen_t screen) {
	
	if (screen == GFX_TOP) {
		s_gfx->top_frame= s_gfx->bottom_frame+1 % 8000;
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
	} else {
		s_gfx->bottom_frame= s_gfx->bottom_frame+1 % 8000;
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
	}
 
	
}

//This should be called after start_draw()
void end_draw() {
	sf2d_end_frame(); //FRAME END
	
}

void end() {
	sf2d_swapbuffers();
}