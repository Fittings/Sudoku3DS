//#include <string.h>
//#include <stdio.h> //printf
#include <stdlib.h> //malloc

#include <3ds.h>



#include "sudoku.h" //ZZZ might not need this
#include "mylib.h" //mod
#include "gfx.h"




//Load Images
#include "bg_bin.h"
#include "immut_numbers_bin.h"
#include "mut_numbers_bin.h"
#include "selector_bin.h"

//Screen resolutions
#define TOP_W 400
#define TOP_H 240
#define BOT_W 320
#define BOT_H 240

SudokuGFX SudokuGFX_init() {
	sf2d_init();
	SudokuGFX my_gfx = malloc(sizeof *my_gfx);
	if (my_gfx == NULL) {
		free(my_gfx);
		return NULL;
	}
	
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
void draw_background(SudokuGFX s_gfx) {
	sf2d_draw_texture(s_gfx->bg, 0, 0);
}

//Handles victory drawing
void draw_victory(SudokuControl s_control) {
	if (s_control->victory_flag) {
		sf2d_draw_rectangle(390, 230, 10, 10, RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //draw purp victory box
	} else {
		sf2d_draw_rectangle(390, 230, 10, 10, RGBA8(0xFF, 0xFF, 0xFF, 0xFF)); //draw white defeat box
	}
}

//ZZZ 25 is a magic number, Fix this
void draw_sudoku(SudokuControl s_control) {
	int i, size = s_control->sudoku->size;
	int row=0, col=0, val=0;
	int x=0, y=0, offset = 0;
	int x_offset = TOP_W/2 - ((size*25)/2); //ZZZ Can these reach 0 if I use a non 25 size? Does it matter?
	int y_offset = TOP_H/2 - ((size*25)/2);

	

	for (i=0; i < (size*size); i++) {
		row = i % size;
		col = i / size;
		x = row * 25; y = col * 25; 
		//if (row % square) x+=5;
		//if (col % square) y+=5;
		x += x_offset; y += y_offset;
		
		val = s_control->sudoku->sudoku_array[i];
		
		if (s_control->sudoku->edit_array[i]) { //draw mutable block
			sf2d_draw_texture_part(s_control->sudoku_gfx->mut_numbers, x, y, val*25, 0, 25, 25);
		} else { //else draw immutable block
			sf2d_draw_texture_part(s_control->sudoku_gfx->immut_numbers, x, y, val*25, 0, 25, 25);
		}
		row++;
	} 
	
	sf2d_draw_line(x_offset, y_offset, x_offset+(size*25), y_offset, RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //TOP_HOR LINE
	sf2d_draw_line(x_offset, y_offset+(size*25), x_offset+(size*25), y_offset+(size*25), RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //BOT_HOR LINE
	sf2d_draw_line(x_offset, y_offset, x_offset, y_offset+(size*25), RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //LEFT_VERT LINE
	sf2d_draw_line(x_offset+(size*25), y_offset, x_offset+(size*25), y_offset+(size*25), RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //RIGHT_VERT LINE
}

void draw_selector(SudokuControl s_control) {
	int size = s_control->sudoku->size;
	
	int x_offset = TOP_W/2 - ((size*25)/2); //ZZZ Can these reach 0 if I use a non 25 size? Does it matter?
	int y_offset = TOP_H/2 - ((size*25)/2);
	
	sf2d_draw_texture(s_control->sudoku_gfx->selector, s_control->cursor%size * 25 +x_offset , s_control->cursor/size * 25 +y_offset);
}



//Handles all drawing
void draw(SudokuControl s_control) {
	sf2d_start_frame(GFX_TOP, GFX_LEFT); //FRAME BEGIN
	
	//Draw background!
	draw_background(s_control->sudoku_gfx);
	//Draw victory!
	draw_victory(s_control);
	//Draw current sudoku state
	draw_sudoku(s_control);
	//Draw current selector state
	draw_selector(s_control);
	
	
	
	sf2d_end_frame(); //FRAME END
	
	s_control->flip = 1 - s_control->flip;// delete
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
	if (s_control->flip) {
		sf2d_draw_rectangle(0, 230, 10, 10, RGBA8(0xFF, 0xFF, 0xFF, 0xFF)); //draw victory box WHITE
	} else {
		sf2d_draw_rectangle(0, 230, 10, 10, RGBA8(0xFF, 0x00, 0xFF, 0xFF)); //draw victory box PURP
	}
	sf2d_end_frame();
	
	sf2d_swapbuffers();
	
}