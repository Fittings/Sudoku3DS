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




//Draws everything
void draw(SudokuControl s_control) {
	sf2d_start_frame(GFX_TOP, GFX_LEFT); //FRAME BEGIN
	
	//ZZZ TEST BOX
	sf2d_draw_rectangle(390, 230, 10, 10, RGBA8(0xFF, 0xFF, 0xFF, 0xFF)); //draw victory box
	
	sf2d_end_frame(); //FRAME END
	sf2d_swapbuffers();
	
}