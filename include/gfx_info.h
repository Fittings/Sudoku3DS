#ifndef GFX_H_
#define GFX_H_

#include <sf2d.h>
#include <sfil.h>

//Screen resolutions
#define TOP_W 400
#define TOP_H 240
#define BOTTOM_W 320
#define BOTTOM_H 240
#define TILE_SIZE 25



struct _SudokuGFX {
	sf2d_texture *bg1, *bg2, *icon, *text_sudoku3ds;
	sf2d_texture *immut_numbers, *mut_numbers, *selector;
	sf2d_texture *start_menu, *start_selector, *text_quit_game, *text_reset, *text_main_menu;
	
	int top_frame, bottom_frame, victory_frame, bg_count;
}; 
typedef struct _SudokuGFX *SudokuGFX; 




extern SudokuGFX SudokuGFX_init();
extern void sudoku_gfx_free(SudokuGFX s_gfx);

extern void init_background(SudokuGFX s_gfx);


extern void draw_board();




extern void start_draw(SudokuGFX s_gfx, gfxScreen_t screen);
extern void end_draw();
extern void end(); //ZZZ consider refactoring this



#endif