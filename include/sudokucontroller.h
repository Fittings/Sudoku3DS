#ifndef SUDOKUCONTROL_H_
#define SUDOKUCONTROL_H_

#include <3ds.h>





struct _SudokuControl {
	int percentage;

	int cursor, start_cursor;
	int new_value, value; //ZZZ Might not even need this?
	int exit_flag;
	int start_menu_flag;
	int victory_flag;
	int flip; //ZZZ
	//Input Values
	u32 kDown;  
	
	//Structs (Forward Declaration)
	struct _SudokuGFX *sudoku_gfx;
	struct _Sudoku *sudoku;

};
typedef struct _SudokuControl *SudokuControl;



//Main Game State
extern void check_main_input(SudokuControl s_control);
extern void update_main_state(SudokuControl s_control);
extern void draw_main_state_top(SudokuControl s_control);
extern void draw_main_state_bottom(SudokuControl s_control);

//Start Menu State
extern void check_start_input(SudokuControl s_control);
extern void update_start_state(SudokuControl s_control);
extern void draw_start_state_top(SudokuControl s_control);
extern void draw_start_state_bottom(SudokuControl s_control);

extern void control_game(SudokuControl s_control);
extern void draw_game(SudokuControl s_control);
extern SudokuControl initialize_game(int size, int percentage);
extern void sudoku_control_free(SudokuControl s_control);



#endif