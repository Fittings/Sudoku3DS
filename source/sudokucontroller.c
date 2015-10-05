

#include "sudoku.h" // Sudoku backend
#include "sudokucontroller.h"
#include "gfx_info.h" // This is the gfx controller. ZZZ Not sure I would call it a controller?
#include "startgfx.h" // For drawing the start menu
#include "bggfx.h" // For drawing the bg
#include "sudokugfx.h" //For drawing the sudoku puzzle
#include "menugfx.h" //For drawing the main menu
#include "victorygfx.h" //For drawing the victory screen

#define START_SIZE 3



void check_input(SudokuControl s_control) {
	hidScanInput();
	s_control->kDown = hidKeysDown();
	if (!s_control->allow_input_flag) return; //Exit if input is disabled.
	if (s_control->start_menu_flag) {
		check_start_input(s_control);
	} else { //main game
		check_main_input(s_control);
	}
}

//takes keys_down and all that
void check_main_input(SudokuControl s_control) { 
	
	int size = s_control->sudoku->size; 
	
	//Check key_presses
	if (s_control->kDown & KEY_A) {
		s_control->new_value = mod((s_control->sudoku)->sudoku_array[s_control->cursor]+1, size+1);
	} else if (s_control->kDown & KEY_B) { //B
		s_control->new_value = mod(s_control->sudoku->sudoku_array[s_control->cursor]-1, size+1);
	} else if (s_control->kDown & KEY_X) { //X
		s_control->new_value = 0;
	} else if (s_control->kDown & KEY_Y) { //Y
		s_control->new_value = 0;
	} else if (s_control->kDown & KEY_DOWN) { //down
		s_control->cursor = mod((s_control->cursor + size), (size*size)); 
	} else if (s_control->kDown & KEY_UP) { //up
		s_control->cursor = mod((s_control->cursor - size), (size*size));
	} else if (s_control->kDown & KEY_LEFT) { //left
		int new_col = mod((s_control->cursor-1), size); //need to use mod as % doesn't work for negatives.
		s_control->cursor = s_control->cursor - (s_control->cursor % size) + new_col;
	} else if (s_control->kDown & KEY_RIGHT) { //right
		int new_col = (s_control->cursor+1) % size;
		s_control->cursor = s_control->cursor - (s_control->cursor % size) + new_col;
	} else if (s_control->kDown & KEY_START) { //start
		s_control->start_menu_flag = 1;
	} else if (s_control->kDown & KEY_SELECT) { //select
		s_control->exit_flag = 1;
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
	
	check_input(s_control); //Get input for board
	//Update with input
	update_sudoku_input(s_control);
	//s_control->victory_flag = check_all(s_control->sudoku);
	if (s_control->victory_flag) {
		s_control->score++;                    
		update_victory_state(s_control);
	}
	
	
} 

void draw_main_state_top(SudokuControl s_control) {
	draw_top_background(s_control->sudoku_gfx); //Draw background!
}

void draw_main_state_bottom(SudokuControl s_control) {
	int size = s_control->sudoku->size;
	int x_offset = BOTTOM_W/2 - ((size*TILE_SIZE)/2) - (2 * 2); 
	int y_offset = 2 + BOTTOM_H/2 - ((size*TILE_SIZE)/2) - (2 * 2); //ZZZ A little bit of magic numbers 
	draw_bottom_background(s_control->sudoku_gfx);
	draw_sudoku(s_control->sudoku_gfx, s_control->sudoku->sudoku_array, s_control->sudoku->edit_array, size, x_offset, y_offset, s_control->cursor);
	
}




//Input handling for when the start menu is open
void start_menu_action(SudokuControl s_control) {
	switch (s_control->start_cursor) {
		case 0:
			sudoku_reset(s_control->sudoku); //Reset edited board to original state
			s_control->start_menu_flag = 0;
			//ZZZ RESET GAME
			break;
		case 1: 
			s_control->main_menu_flag = 1;
			break;
		case 2: 
			s_control->start_menu_flag = 0;
			s_control->exit_flag = 1; //Quit game
			break;
		default:
			s_control->start_menu_flag = 0;
			s_control->exit_flag = 1; //Quit game
			break;
	}
}

void check_start_input(SudokuControl s_control) {

	//Check key_presses
	if (s_control->kDown & KEY_A) { //A
		start_menu_action(s_control);
	} else if (s_control->kDown & KEY_B) { //B
		s_control->start_menu_flag = 0;
	} else if (s_control->kDown & KEY_DOWN) { //down
		s_control->start_cursor = mod(s_control->start_cursor+1, START_SIZE);
	} else if (s_control->kDown & KEY_UP) { //up
		s_control->start_cursor = mod(s_control->start_cursor-1, START_SIZE);
	} else if (s_control->kDown & KEY_START) { //start
		s_control->start_menu_flag = 0;
	} else if (s_control->kDown & KEY_SELECT) { //select
		s_control->exit_flag = 1;
	}

	
}

//Call to check input relating to the start menu and update it.
void update_start_state(SudokuControl s_control) {
	check_input(s_control);
}

//Draws the start state on the top screen. This is seperated in case some extra calculations need to be done here
void draw_start_state_top(SudokuControl s_control) {
	draw_start_gfx_top(s_control->sudoku_gfx, s_control->start_cursor);
}

//Draws the start state on the bot screen. This is seperated in case some extra calculations need to be done here
void draw_start_state_bottom(SudokuControl s_control) {
	draw_start_gfx_bottom(s_control->sudoku_gfx);
}

void check_main_menu_input(SudokuControl s_control) {
	hidScanInput();
	s_control->kDown = hidKeysDown();
	if (s_control->kDown & KEY_START) {
		s_control->main_menu_flag = 0;
		reset_control_state(s_control);
		create_new_game(s_control);
		
	} else if (s_control->kDown & KEY_L) {
		s_control->percentage = s_control->percentage+5;
		if (s_control->percentage > 90) s_control->percentage = 90;
	} else if (s_control->kDown & KEY_R) {
		s_control->percentage = s_control->percentage-5;
		if (s_control->percentage < 30) s_control->percentage = 30;
	}
}

void update_main_menu_state(SudokuControl s_control) {
	check_main_menu_input(s_control);
}



//Controls the game input/update/draw flow.
void control_game(SudokuControl s_control) {
	if (s_control->main_menu_flag == 1) { //ALL Main menu control and drawing is here.
		update_main_menu_state(s_control); 
		
		start_draw(s_control->sudoku_gfx, GFX_LEFT); //DRAW TOP
		draw_main_menu_bg(s_control->sudoku_gfx, GFX_TOP);
		draw_main_menu_logo(s_control->sudoku_gfx);
		//draw_main_menu_start(s_control->sudoku_gfx);
		end_draw();
		 
		start_draw(s_control->sudoku_gfx, GFX_BOTTOM); //DRAW BOTTOM
		draw_main_menu_bg(s_control->sudoku_gfx, GFX_TOP);
		draw_main_menu_difficulty(s_control->sudoku_gfx, s_control->percentage);
		end_draw();
		
		end();
	
	
		return;
	}
		
	if (s_control->start_menu_flag == 1) { //Enter Start menu
		update_start_state(s_control);
	} else { //else we are controlling the board.
		update_main_state(s_control);	
	}
	if (check_all(s_control->sudoku)) {
		s_control->victory_flag = 1;
	}
	draw_game(s_control);
	
}

//zzz Need to make sure everything is being reset here.
void reset_control_state(SudokuControl s_control) {
	create_new_game(s_control); //Creates a new game
	s_control->start_menu_flag = 0;
	s_control->start_cursor = 0;
	s_control->cursor = 0,
	s_control->main_cursor = 0;
	s_control->exit_flag = 0;
	s_control->victory_flag = 0;
	s_control->allow_input_flag = 1;
	s_control->reset_flag = 0;
	s_control->main_menu_flag = 0;
	s_control->score = 0;
}


//This is used to create a new game on victory.
void create_new_game(SudokuControl s_control) {
	s_control->sudoku_gfx->victory_frame = 0;
	s_control->allow_input_flag = 1;
	s_control->victory_flag = 0;
	s_control->value = s_control->sudoku->sudoku_array[s_control->cursor];
	s_control->new_value = s_control->value; //ZZZ Is this needed?
	sudoku_remake(s_control->sudoku, s_control->percentage);
}


void update_victory_state(SudokuControl s_control) {
	s_control->allow_input_flag = 0;
	s_control->sudoku_gfx->victory_frame++;
	if (s_control->sudoku_gfx->victory_frame > 400) { //Let victory frames go for this length
		create_new_game(s_control);
	}
}

void draw_game(SudokuControl s_control) {
//DRAW STATE TOP
	start_draw(s_control->sudoku_gfx, GFX_TOP); 
	draw_main_state_top(s_control);	//draw game top
	if (s_control->victory_flag) {
		update_victory_state(s_control);
		draw_victory(s_control->sudoku_gfx, GFX_TOP);
	}
	if (s_control->start_menu_flag == 1) draw_start_state_top(s_control);//draw_start_state_top;
	
	end_draw(); 
	//END TOP
	
	//DRAW STATE BOTTOM
	start_draw(s_control->sudoku_gfx, GFX_BOTTOM);
	draw_main_state_bottom(s_control);	//draw game bottom
	if (s_control->victory_flag) draw_victory(s_control->sudoku_gfx, GFX_BOTTOM);
	if (s_control->start_menu_flag == 1) draw_start_state_bottom(s_control); //draw start bottom
	end_draw(); 
	end();
	//END BOTTOM

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
	s_control->sudoku = sudoku_unique_setup(size, percentage, svcGetSystemTick());
	
	//Set-up variable states
	s_control->percentage = percentage;
	s_control->value = s_control->sudoku->sudoku_array[s_control->cursor];
	s_control->new_value = s_control->value; //ZZZ Is this needed?
	s_control->start_menu_flag = 0;
	s_control->start_cursor = 0;
	s_control->cursor = 0, s_control->percentage = percentage;
	s_control->main_cursor = 0;
	s_control->exit_flag = 0;
	s_control->victory_flag = 0;
	s_control->allow_input_flag = 1;
	s_control->reset_flag = 0;
	s_control->main_menu_flag = 1;
	s_control->score = 0;
	
	
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
