#ifndef SUDOKUCONTROL_H_
#define SUDOKUCONTROL_H_

#include "gfx.h"


struct _SudokuControl {
	int percentage;
	int size;
	int cursor;
	int new_value, value; //ZZZ Might not even need this?
	int exit_flag;
	//Input Values
	u32 kDown;  
	
	
	SudokuGFX sudoku_gfx;
	Sudoku sudoku;
	//sf2d_texture *bg, *immut_numbers, *mut_numbers, *selector;
};
typedef struct _SudokuControl *SudokuControl;

extern void check_input(SudokuControl s_control);
extern void update_state(SudokuControl s_control);
extern SudokuControl initialize_game(int size, int percentage);



#endif