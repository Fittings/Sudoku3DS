#ifndef SUDOKUCONTROL_H_
#define SUDOKUCONTROL_H_

#include <3ds.h>





struct _SudokuControl {
	int percentage;
	int size;
	int cursor;
	int new_value, value; //ZZZ Might not even need this?
	int exit_flag;
	//Input Values
	u32 kDown;  
	
	//Structs (Forward Declaration)
	struct _SudokuGFX *sudoku_gfx;
	struct _Sudoku *sudoku;

};
typedef struct _SudokuControl *SudokuControl;




extern void check_input(SudokuControl s_control);
extern void update_state(SudokuControl s_control);
extern SudokuControl initialize_game(int size, int percentage);
extern void sudoku_control_free(SudokuControl s_control);



#endif