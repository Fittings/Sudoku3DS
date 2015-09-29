//#include <string.h>
//#include <stdio.h> //printf
#include <stdlib.h> //malloc

#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>


#include "sudoku.h" //Need this to draw a view
//#include "mylib.h" //mod
#include "gfx.h"




//Load Images
#include "bg_bin.h"
#include "immut_numbers_bin.h"
#include "mut_numbers_bin.h"
#include "selector_bin.h"

SudokuGFX SudokuGFX_init() {
	sf2d_init();
	SudokuGFX my_gfx = malloc(sizeof *my_gfx);
	//Load all images
	my_gfx->bg 				= sfil_load_PNG_buffer(bg_bin, SF2D_PLACE_RAM);
	my_gfx->immut_numbers 	= sfil_load_PNG_buffer(immut_numbers_bin, SF2D_PLACE_RAM);
	my_gfx->mut_numbers 	= sfil_load_PNG_buffer(mut_numbers_bin, SF2D_PLACE_RAM);
	my_gfx->selector		= sfil_load_PNG_buffer(selector_bin, SF2D_PLACE_RAM);
	
	return my_gfx;
}

//ZZZ Might be silly to put free in a function
void sudoku_gfx_free(SudokuGFX s_gfx) {
	free(s_gfx);
}




//draws everything!
void draw(Sudoku sudoku) {
	sf2d_start_frame(GFX_TOP, GFX_LEFT); //FRAME BEGIN
	
	//ZZZ TEST BOX
	sf2d_draw_rectangle(390, 230, 10, 10, RGBA8(0xFF, 0xFF, 0xFF, 0xFF)); //ZZZdraw victory box
	
	sf2d_end_frame(); //FRAME END
	sf2d_swapbuffers();
	
}