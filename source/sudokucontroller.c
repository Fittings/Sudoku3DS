//#include <string.h> //strcat
//#include <stdio.h> //printf
#include <stdlib.h> //malloc
//#include <math.h> //sqrt


#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include <3ds.h>
#include "mylib.h" //mod


#include "sudoku.h"
#include "sudokucontroller.h"
#include "gfx.h" 


//ZZZ #include <sf2d.h>
//ZZZ #include <sfil.h>





//takes keys_down and all that
void check_input(SudokuControl s_control) {
	hidScanInput();
	s_control->kDown = hidKeysDown();


	
	if (s_control->kDown & KEY_A) {
		s_control->new_value = mod(s_control->sudoku->sudoku_array[s_control->cursor]+1, s_control->sudoku->size+1);
	} else if (s_control->kDown & KEY_B) {
		s_control->new_value = mod(s_control->sudoku->sudoku_array[s_control->cursor]-1, s_control->size+1);
	} else if (s_control->kDown & KEY_DOWN) {
		s_control->cursor = mod((s_control->cursor + s_control->size), (s_control->size*s_control->size)); 
	} else if (s_control->kDown & KEY_UP) {
		s_control->cursor = mod((s_control->cursor - s_control->size), (s_control->size*s_control->size));
	} else if (s_control->kDown & KEY_LEFT) {
		s_control->cursor = mod((s_control->cursor - 1), (s_control->size*s_control->size));
	} else if (s_control->kDown & KEY_RIGHT) {
		s_control->cursor = mod((s_control->cursor + 1), (s_control->size*s_control->size));
	} else if (s_control->kDown & KEY_START) {
		s_control->exit_flag = 1;
	}
}



void update_state(SudokuControl s_control) {
	//Check for any input
	check_input(s_control);
	
	//Update with input
	if (s_control->new_value != s_control->value && s_control->sudoku->edit_array[s_control->cursor] == 1) {
		s_control->sudoku->sudoku_array[s_control->cursor] = s_control->new_value;
	}
	
	//Draw state
	draw(s_control->sudoku_gfx);
}

/* Initializes all the variables used for tracking. 
 * As well as setting up the game state and loading textures. */
SudokuControl initialize_game(int size, int percentage) {
	SudokuControl s_control = malloc(sizeof *s_control); 
	
	//Set-up sudoku
	s_control->sudoku = sudoku_new(size); 
	sudoku_default(s_control->sudoku); 
	sudoku_transform(s_control->sudoku);  
	sudoku_delete_space(s_control->sudoku, percentage);
	
	//Set-up variable states
	s_control->value = s_control->sudoku->sudoku_array[s_control->cursor];
	s_control->new_value = s_control->value; //ZZZ Is this needed?
	s_control->cursor = 0, s_control->percentage = percentage;
	s_control->exit_flag = 0;
	
	//Set-up textures
	s_control->sudoku_gfx = SudokuGFX_init();

	return s_control;
}
