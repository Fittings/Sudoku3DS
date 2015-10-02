

#include "sudoku.h"
#include "sudokucontroller.h"
#include "gfx.h"

#define START_SIZE 3



//takes keys_down and all that
void check_main_input(SudokuControl s_control) { 
	hidScanInput();
	s_control->kDown = hidKeysDown();
	int size = s_control->sudoku->size; 
	
	//Check key_presses
	if (s_control->kDown & KEY_A) {
		s_control->new_value = mod((s_control->sudoku)->sudoku_array[s_control->cursor]+1, size+1);
	} else if (s_control->kDown & KEY_B) { //B
		s_control->new_value = mod(s_control->sudoku->sudoku_array[s_control->cursor]-1, size+1);
	} else if (s_control->kDown & KEY_DOWN) { //down
		s_control->cursor = mod((s_control->cursor + size), (size*size)); 
	} else if (s_control->kDown & KEY_UP) { //up
		s_control->cursor = mod((s_control->cursor - size), (size*size));
	} else if (s_control->kDown & KEY_LEFT) { //left
		s_control->cursor = mod((s_control->cursor - 1), (size*size));
	} else if (s_control->kDown & KEY_RIGHT) { //right
		s_control->cursor = mod((s_control->cursor + 1), (size*size));
	} else if (s_control->kDown & KEY_START) { //start
		s_control->exit_flag = 1;
	} else if (s_control->kDown & KEY_SELECT) { //select
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

//Updates the s_control struct with 
void update_sudoku_input(SudokuControl s_control) {
	if (!s_control->kDown) return; //No key press.
	
	//If the sudoku position can be updated, then update.
	if (s_control->new_value != s_control->value && s_control->sudoku->edit_array[s_control->cursor] == 1) {
		s_control->sudoku->sudoku_array[s_control->cursor] = s_control->new_value;
	}
	//reset the value checks
	s_control->value = s_control->sudoku->sudoku_array[s_control->cursor];
	s_control->new_value = s_control->value;
}


//Updates
void update_main_state(SudokuControl s_control) {
	
	check_main_input(s_control); //Get input for board
	//Update with input
	update_sudoku_input(s_control);
	update_victory_state(s_control);
	
	
} 

void draw_main_state(SudokuControl s_control) {
	int size = s_control->sudoku->size; 
	int x_offset = TOP_W/2 - ((size*TILE_SIZE)/2); 
	int y_offset = TOP_H/2 - ((size*TILE_SIZE)/2);
	//DRAW STATE TOP
	start_draw(s_control->sudoku_gfx, GFX_TOP); 
		draw_top_background(s_control->sudoku_gfx); //Draw background!
	end_draw(); 
	//END TOP
	
	x_offset = BOTTOM_W/2 - ((size*TILE_SIZE)/2) - (2 * 2); 
	y_offset =2 + BOTTOM_H/2 - ((size*TILE_SIZE)/2) - (2 * 2);
	
	//DRAW STATE BOTTOM
	start_draw(s_control->sudoku_gfx, GFX_BOTTOM);
		draw_bottom_background(s_control->sudoku_gfx);
		//Draw sudoku
		draw_sudoku(s_control->sudoku_gfx, s_control->sudoku->sudoku_array, s_control->sudoku->edit_array, size, x_offset, y_offset, s_control->cursor);
		draw_victory(s_control->victory_flag); //Draw victory!
	end_draw(); 
	end();
	//END BOTTOM
}

//Input handling for when the start menu is open
void check_start_input(SudokuControl s_control) {
	hidScanInput();
	s_control->kDown = hidKeysDown();
	
	if (s_control->kDown) {
		if (KEY_DOWN) {
			s_control->start_cursor = s_control->start_cursor + 1 % START_SIZE;
		} else if (KEY_UP) {
			s_control->start_cursor = s_control->start_cursor + 1 % START_SIZE;
		} else if (KEY_A) {
			//do action at a. How do I implement this? Maybe a switch in another function.
		} else if (KEY_B || KEY_START) { //exit menu
			s_control->start_menu_flag = 0;
		} 
	}
}

void update_start_state(SudokuControl s_control) {
	//do
}

void control_game(SudokuControl s_control) {
	draw_main_state(s_control);	//draw game
	if (s_control->start_menu_flag == 1) {
		//update_start_state(s_control);
		//Check for input
	} else { //else we are controlling the board.
		update_main_state(s_control);	
	}
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
	s_control->start_menu_flag = 0;
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
