#ifndef GFX_H_
#define GFX_H_

#include <sf2d.h>
#include <sfil.h>

//ZZZ Do I need this struct?
struct _SudokuGFX {
	sf2d_texture *bg, *immut_numbers, *mut_numbers, *selector;
}; 
typedef struct _SudokuGFX *SudokuGFX; 


extern SudokuGFX SudokuGFX_init();
extern void draw_victory();
extern void draw_board();
extern void draw_bg();

extern void draw();

#endif