#ifndef SUDOKUCONTROL_H_
#define SUDOKUCONTROL_H_


#include <3ds.h>




struct _SudokuControl {
	int percentage;

	int cursor, start_cursor, main_cursor;
	int new_value, value; //ZZZ Might not even need this?
	int start_menu_flag, main_menu_flag, allow_input_flag, victory_flag, exit_flag, reset_flag;
	int score; //ZZZ
	//Input Values
	u32 kDown;  
	
	//Structs (Forward Declaration)
	struct _SudokuGFX *sudoku_gfx;
	struct _Sudoku *sudoku;

};
typedef struct _SudokuControl *SudokuControl;

extern void check_input(SudokuControl s_control);

//Main Game State
extern void check_main_input(SudokuControl s_control);
extern void update_main_state(SudokuControl s_control);
extern void draw_main_state_top(SudokuControl s_control);
extern void draw_main_state_bottom(SudokuControl s_control);

//Start Menu State
extern void start_menu_action(SudokuControl s_control);
extern void check_start_input(SudokuControl s_control);
extern void update_start_state(SudokuControl s_control);
extern void draw_start_state_top(SudokuControl s_control);
extern void draw_start_state_bottom(SudokuControl s_control);

//Victory State


extern void check_start_input(SudokuControl s_control);
extern void check_main_menu_input(SudokuControl s_control);
extern void update_main_menu_state(SudokuControl s_control);

extern void control_game(SudokuControl s_control);
extern void reset_control_state(SudokuControl s_control);
extern void create_new_game(SudokuControl s_control);
extern void update_victory_state(SudokuControl s_control);
extern void draw_game(SudokuControl s_control);
extern SudokuControl initialize_game(int size, int percentage);
extern void sudoku_control_free(SudokuControl s_control);



#endif