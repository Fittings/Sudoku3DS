//#include <string.h>
//#include <stdio.h> //printf
#include <stdlib.h> //malloc

#include <3ds.h>
#include <math.h> //sqrt



#include "sudoku.h" //ZZZ might not need this
#include "mylib.h" //mod
#include "gfx.h"




//Load Images
#include "bg_bin.h"
#include "immut_numbers_bin.h"
#include "mut_numbers_bin.h"
#include "selector_bin.h"



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
	//Load all images
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
		free(s_gfx);
	}
}

//Handles background drawing 
void draw_background(SudokuGFX s_gfx, gfxScreen_t screen) {
	
	if (screen == GFX_TOP) {

		int mini_box_sz = 5, i, j, x=0, y=0, y_offset = 0, x_offset = 0;
		sf2d_draw_rectangle(0, 0, TOP_W, TOP_H, RGBA8(0xF2, 0xF2, 0xF2, 0xFF));  //draw plain bg
		
		//sf2d_draw_rectangle(0, 2, TOP_W, TOP_H/7, RGBA8(0xE9, 0x6E, 0x9C, 0xbE)); //draw status bar
		for (j=0; j < 40 ; j++) {			
			y = j + y_offset + 1;
			
			for (i=0; i < 64 ; i++) {
				x = i;
				x = (i + s_gfx->top_frame + x_offset) % (TOP_W+50);
				x -= (50);
				if (j % 2) {
					//x = 64 - x;
				} 
				
				
				
				if (i%2 == 0) { //RGBA8(0xF4, 0xE1, 0xE5, 0xbE)
					sf2d_draw_rectangle(x, y, mini_box_sz, mini_box_sz, RGBA8(0xE9, 0x6E, 0x9C, 0xbE));
				} else {
					sf2d_draw_rectangle(x, y, mini_box_sz, mini_box_sz, RGBA8(0xFA, 0xDC, 0xE4, 0xbE));
				}
				
		
				x_offset += 6;
				
				
			}
			
			x_offset = 0;
			y_offset += 6;
			
			

			
			
		}
		
		//sf2d_draw_rectangle(398, 30, mini_box_sz, mini_box_sz, RGBA8(0xE9, 0x6E, 0x9C, 0xbE));
		
		
	} else {
		sf2d_draw_texture(s_gfx->bg, 0, 0);
	}
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
void draw_sudoku(SudokuGFX s_gfx, int *sudoku_array, int *edit_array, int size, int x_offset, int y_offset) {
	int i, square = sqrt(size);
	int row=0, col=0, val=0;
	int x=0, y=0;// offset = 0;
	//int puzzle_width = size*TILE_SIZE;
	int x_div_offset = 0;
	int y_div_offset = 0;
	
	//
	
	

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
		row++;
	} 
	//x_offset += (sqrt(size)-1)*5;
	//y_offset += (sqrt(size)-1)*5;
	
	//sf2d_draw_line(x_offset, y_offset, x_offset+(puzzle_width), y_offset, RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //TOP_HOR LINE
	//sf2d_draw_line(x_offset, y_offset+(puzzle_width), x_offset+(puzzle_width), y_offset+(puzzle_width), RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //BOT_HOR LINE
	//sf2d_draw_line(x_offset, y_offset, x_offset, y_offset+(puzzle_width), RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //LEFT_VERT LINE
	//sf2d_draw_line(x_offset+(puzzle_width), y_offset, x_offset+(puzzle_width), y_offset+(puzzle_width), RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //RIGHT_VERT LINE
}

void draw_selector(SudokuGFX s_gfx, int cursor, int size, int x_offset, int y_offset) {
	sf2d_draw_texture(s_gfx->selector, cursor%size * TILE_SIZE +x_offset , cursor/size * TILE_SIZE +y_offset);
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