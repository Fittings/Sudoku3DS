#ifndef GFX_H_
#define GFX_H_


#include <sf2d.h>
#include <sfil.h>
//#include "sudokucontroller.h"

//Screen resolutions
#define TOP_W 400
#define TOP_H 240
#define BOTTOM_W 320
#define BOTTOM_H 240
#define TILE_SIZE 25



struct _SudokuGFX {
	sf2d_texture *bg, *immut_numbers, *mut_numbers, *selector;
	int top_frame, bottom_frame;
}; 
typedef struct _SudokuGFX *SudokuGFX; 




extern SudokuGFX SudokuGFX_init();
extern void sudoku_gfx_free(SudokuGFX s_gfx);

extern void draw_board();
extern void draw_background(SudokuGFX s_gfx) ;
extern void draw_victory(int victory_flag);
extern void draw_sudoku(SudokuGFX s_gfx, int *sudoku_array, int *edit_array, int size, int x_offset, int y_offset);
extern void draw_selector(SudokuGFX s_gfx, int cursor, int size, int x_offset, int y_offset);
//extern void draw(SudokuControl s_control);
extern void start_draw(SudokuGFX s_gfx, gfxScreen_t screen);
extern void end_draw();
extern void end(); //ZZZ consider refactoring this



#endif