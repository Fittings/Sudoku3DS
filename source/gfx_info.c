#include <stdlib.h> //malloc
#include <3ds.h>
#include "sudoku.h" //ZZZ might not need this
#include "gfx_info.h"

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
 */




SudokuGFX SudokuGFX_init() {
	sf2d_init();
	SudokuGFX my_gfx = malloc(sizeof *my_gfx);
	if (my_gfx == NULL) {
		free(my_gfx);
		return NULL;
	}
	my_gfx->top_frame = 0;
	my_gfx->bottom_frame = 0;
	my_gfx->bg_count = 0;
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