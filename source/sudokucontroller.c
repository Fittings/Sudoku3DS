

#include "sudoku.h"
#include "sudokucontroller.h"
#include "gfx.h"




//takes keys_down and all that
void check_input(SudokuControl s_control) { //ZZZOPTIMIZE - draw only when change occurs
	hidScanInput();
	s_control->kDown = hidKeysDown();
	int size = s_control->sudoku->size; //shorten the reference


	//Check key_presses
	if (s_control->kDown & KEY_A) {
		s_control->new_value = mod((s_control->sudoku)->sudoku_array[s_control->cursor]+1, size+1);
	} else if (s_control->kDown & KEY_B) {
		s_control->new_value = mod(s_control->sudoku->sudoku_array[s_control->cursor]-1, size+1);
	} else if (s_control->kDown & KEY_DOWN) {
		s_control->cursor = mod((s_control->cursor + size), (size*size)); 
	} else if (s_control->kDown & KEY_UP) {
		s_control->cursor = mod((s_control->cursor - size), (size*size));
	} else if (s_control->kDown & KEY_LEFT) {
		s_control->cursor = mod((s_control->cursor - 1), (size*size));
	} else if (s_control->kDown & KEY_RIGHT) {
		s_control->cursor = mod((s_control->cursor + 1), (size*size));
	} else if (s_control->kDown & KEY_START) {
		s_control->exit_flag = 1;
	}
}

void update_victory_state(SudokuControl s_control) {
	if (check_all(s_control->sudoku)) {
		s_control->victory_flag = 1;
	} else {
		s_control->victory_flag = 0;
	}
}

void update_sudoku_input(SudokuControl s_control) {
	if (!s_control->kDown) return; 
	

	if (s_control->new_value != s_control->value && s_control->sudoku->edit_array[s_control->cursor] == 1) {
		s_control->sudoku->sudoku_array[s_control->cursor] = s_control->new_value;
	}
	s_control->value = s_control->sudoku->sudoku_array[s_control->cursor];
	s_control->new_value = s_control->value;
}



void update_state(SudokuControl s_control) {
	//Check for any input
	check_input(s_control);
	
	//Update with input
	update_sudoku_input(s_control);
	update_victory_state(s_control);
	
	
	
	//Draw state
	draw(s_control);
} 

/* Initializes all the variables used for tracking. 
 * As well as setting up the game state and loading textures. */
SudokuControl initialize_game(int size, int percentage) {
	SudokuControl s_control = malloc(sizeof *s_control); 
	if (s_control == NULL) return NULL;
	
	//Set-up sudoku
	s_control->sudoku = malloc(sizeof s_control->sudoku);
	if (s_control->sudoku == NULL) {
		free(s_control);
		return NULL;
	}
	s_control->sudoku = sudoku_new(size); 
	sudoku_default(s_control->sudoku); 
	sudoku_transform(s_control->sudoku);  
	sudoku_delete_space(s_control->sudoku, percentage);
	
	//Set-up variable states
	s_control->value = s_control->sudoku->sudoku_array[s_control->cursor];
	s_control->new_value = s_control->value; //ZZZ Is this needed?
	s_control->cursor = 0, s_control->percentage = percentage;
	s_control->exit_flag = 0;
	s_control->victory_flag = 0;
	s_control->flip = 0;
	
	//Set-up textures
	s_control->sudoku_gfx = malloc(sizeof s_control->sudoku_gfx);
	if (s_control->sudoku == NULL) {
		sudoku_free(s_control->sudoku); free(s_control);
		return NULL;
	}
	s_control->sudoku_gfx = SudokuGFX_init(); 

	return s_control;
}


void sudoku_control_free(SudokuControl s_control) {
	if (s_control != NULL) {
		sudoku_free(s_control->sudoku);
		sudoku_gfx_free(s_control->sudoku_gfx);
		free(s_control);
	}
} 
