#ifndef GFX_H_
#define GFX_H_


#include <sf2d.h>
#include <sfil.h>
#include "sudokucontroller.h"




//ZZZ Do I need this struct?
struct _SudokuGFX {
	sf2d_texture *bg, *immut_numbers, *mut_numbers, *selector;
}; 
typedef struct _SudokuGFX *SudokuGFX; 


//Need this to draw a view
//#include "mylib.h" //mod

#include "sudokucontroller.h"
extern SudokuGFX SudokuGFX_init();
extern void sudoku_gfx_free(SudokuGFX s_gfx);
extern void draw_victory();
extern void draw_board();
extern void draw_bg();
extern void draw(SudokuControl s_control);

//extern void draw(SudokuControl sudoku);

#endif