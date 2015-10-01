//#include <string.h>
//#include <stdio.h> //printf
#include <stdlib.h> //malloc

#include <3ds.h>
#include <math.h> //sqrt



#include "sudoku.h" //ZZZ might not need this
#include "mylib.h" //mod
#include "gfx.h"

#define BG_COL 40 //Need to remove these magic numbers and actually do the maths on this.
#define BG_ROW 75
#define BOX_SIZE 5


//Load Images
#include "bg_bin.h"
#include "immut_numbers_bin.h"
#include "mut_numbers_bin.h"
#include "selector_bin.h"
#include "icon_bin.h"
#include "sudoku3ds_bin.h"



SudokuGFX SudokuGFX_init() {
	sf2d_init();
	SudokuGFX my_gfx = malloc(sizeof *my_gfx);
	if (my_gfx == NULL) {
		free(my_gfx);
		return NULL;
	}
	my_gfx->flip = 0;
	my_gfx->top_frame = 0;
	my_gfx->bottom_frame = 0;
	my_gfx->first_bg_array = malloc(BG_ROW * sizeof my_gfx->first_bg_array[0]);
	my_gfx->second_bg_array = malloc(BG_ROW * sizeof my_gfx->second_bg_array[0]);
	init_background(my_gfx);
	//init_background(my_gfx);
	
	//Load all images
	my_gfx->sudoku3ds_text	= sfil_load_PNG_buffer(sudoku3ds_bin, SF2D_PLACE_RAM);
	my_gfx->icon			= sfil_load_PNG_buffer(icon_bin, SF2D_PLACE_RAM);
	my_gfx->bg 				= sfil_load_PNG_buffer(bg_bin, SF2D_PLACE_RAM);
	my_gfx->immut_numbers 	= sfil_load_PNG_buffer(immut_numbers_bin, SF2D_PLACE_RAM);
	my_gfx->mut_numbers 	= sfil_load_PNG_buffer(mut_numbers_bin, SF2D_PLACE_RAM);
	my_gfx->selector		= sfil_load_PNG_buffer(selector_bin, SF2D_PLACE_RAM);
	
	return my_gfx;
}

//Frees SudokuGFX
void sudoku_gfx_free(SudokuGFX s_gfx) {
	sf2d_fini();
	if (s_gfx != NULL) {
		free(s_gfx->first_bg_array);
		free(s_gfx);
	}
}

void init_background(SudokuGFX s_gfx) {
	int i;
	for (i=0; i < BG_ROW; i++) {
		s_gfx->first_bg_array[i]=i*(BOX_SIZE+1) - 24; //array storing x position of boxes
		s_gfx->second_bg_array[i]=i*(BOX_SIZE+1) - 24;
	}
}

//ZZZ second_bg_array is doing absolutely nothing. This needs to fixed or removed
void update_background_position(SudokuGFX s_gfx) {
	int i;
	for (i=0; i < BG_ROW; i++) {
		s_gfx->first_bg_array[i] = mod(s_gfx->first_bg_array[i]+1, TOP_W + 50 ) - 50;
		s_gfx->second_bg_array[i] = mod(s_gfx->second_bg_array[i]-1, TOP_W + 50 ) - 50;
		
	}
}

//Draws the scrolling boxes on the screen. 
void draw_many_boxes(SudokuGFX s_gfx) {
	int i, j, x, y;
	
	for (i=0; i < TOP_H + 20; i+=6) {
		y = i;
		for (j=0; j < BG_ROW; j++) {
			if (i % 2 == 0) { //if a second row //ZZZ This is not working propery. Probably remove this
				x = s_gfx->first_bg_array[j];
			} else { //if a first row
				x = s_gfx->second_bg_array[j];
			}
			if (j % 2 == 0) { 
				sf2d_draw_rectangle(x, y, BOX_SIZE, BOX_SIZE, RGBA8(0xF4, 0xE1, 0xE5, 0xFF));
			} else {
				sf2d_draw_rectangle(x, y, BOX_SIZE, BOX_SIZE, RGBA8(0xFA, 0xDC, 0xE4, 0xFF));
			}
		} 
	}
}


void draw_top_background(SudokuGFX s_gfx) {
	if (s_gfx->top_frame % 2 == 0) update_background_position(s_gfx);
	sf2d_draw_rectangle(0, 0, TOP_W, TOP_H, RGBA8(0xF2, 0xF2, 0xF2, 0xFF));  //draw plain bg
	draw_many_boxes(s_gfx);
	sf2d_draw_rectangle(0, 0, TOP_W, TOP_H, RGBA8(0xF2, 0xF2, 0xF2, 0x83));
	sf2d_draw_rectangle(0, 2, TOP_W, 32, RGBA8(0xE9, 0x6E, 0x9C, 0xFF)); //draw status bar
	sf2d_draw_texture(s_gfx->icon, 21, 0); //Icon
	sf2d_draw_texture(s_gfx->sudoku3ds_text, -10, 5); //text

}


//ZZZ Probably faster to load this as a texture rather than objects?
extern void draw_bottom_background(SudokuGFX s_gfx) {
	sf2d_draw_rectangle(0, 0, BOTTOM_W, TOP_H, RGBA8(0xF2, 0xF2, 0xF2, 0xFF));
	draw_many_boxes(s_gfx);
	sf2d_draw_rectangle(0, 0, BOTTOM_W, TOP_H, RGBA8(0xF2, 0xF2, 0xF2, 0x93));  //draw plain bg
	sf2d_draw_rectangle(0, -10, BOTTOM_W, 20, RGBA8(0xFA, 0xAA, 0xA3, 0x93)); //peach
	sf2d_draw_rectangle(0, 30, BOTTOM_W, 20, RGBA8(0x8E, 0xCF, 0xB2, 0x93)); //green
	sf2d_draw_rectangle(0, 70, BOTTOM_W, 20, RGBA8(0xE5, 0xCD, 0x7C, 0x93)); //yellow
	sf2d_draw_rectangle(0, 110, BOTTOM_W, 20, RGBA8(0x7B, 0xD3, 0xEA, 0x93)); //blue
	sf2d_draw_rectangle(0, 150, BOTTOM_W, 20, RGBA8(0xC3, 0xA7, 0xE0, 0x93)); //purple
	sf2d_draw_rectangle(0, 190, BOTTOM_W, 20, RGBA8(0xD7, 0x9B, 0xB5, 0x93)); //pink
	sf2d_draw_rectangle(0, 230, BOTTOM_W, 20, RGBA8(0xFA, 0xAA, 0xA3, 0x93)); //peach
	//int x = BOTTOM_W/2 - ((9*TILE_SIZE)/2) - (2 * 2); 
	//int y = BOTTOM_H/2 - ((9*TILE_SIZE)/2) - (2 * 2); 
	//int width = BOTTOM_W - (2 * x);
	//int height = BOTTOM_H - (2 * y);
	//sf2d_draw_rectangle(x, y, width, height, RGBA8(0xF2, 0xF2, 0xF2, 0xFF)); //white box
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
	//int puzzle_width = size*TILE_SIZE;
	int x_div_offset = 0;
	int y_div_offset = 0;

	for (i=0; i < (size*size); i++) {
		row = i % size;
		col = i / size;
		x = row * TILE_SIZE; y = col * TILE_SIZE;
		if (row % (square) == 0) x_div_offset = (row-1)*1;
		if (col % (square) == 0) y_div_offset = (col-1)*1;

		
		
		//if (col % square) y+=5;
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
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		s_gfx->top_frame = 1 + s_gfx->top_frame % 8000;
	} else {
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		s_gfx->bottom_frame = 1 + s_gfx->bottom_frame % 8000;
	}
 
	
}

//This should be called after start_draw()
void end_draw() {
	sf2d_end_frame(); //FRAME END
	
}

void end() {
	sf2d_swapbuffers();
}