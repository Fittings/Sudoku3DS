#include <string.h> //strcat
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <math.h> //sqrt


#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include <3ds.h>



#include "sudoku.h"
#include "mylib.h" //mod

#include <sf2d.h>
#include <sfil.h>


#include "bg_bin.h"
#include "immut_numbers_bin.h"
#include "mut_numbers_bin.h"
#include "selector_bin.h"

#define SU_SIZE 9
#define SU_RAND 99



int percentage;
int size;
int cursor;
int new_value, value;
u32 kDown;
Sudoku my_sudoku;
sf2d_texture *bg, *immut_numbers, *mut_numbers, *selector;










//Loads all the textures used for this program!
void initialize_textures() {
	sf2d_init();
	bg = sfil_load_PNG_buffer(bg_bin, SF2D_PLACE_RAM);
	immut_numbers = sfil_load_PNG_buffer(immut_numbers_bin, SF2D_PLACE_RAM);
	mut_numbers = sfil_load_PNG_buffer(mut_numbers_bin, SF2D_PLACE_RAM);
	selector = sfil_load_PNG_buffer(selector_bin, SF2D_PLACE_RAM);
}

void free_textures() {
	//do free
}

int initialize_game(int the_size, int the_percentage) {
	cursor = 0, percentage = the_percentage;
	//init sudoku
	//draw 
	//set variables
	size = the_size;
	my_sudoku = sudoku_new(size); 
	sudoku_default(my_sudoku); 
	sudoku_transform(my_sudoku); 
	sudoku_delete_space(my_sudoku, percentage);
	
	
	value = my_sudoku->sudoku_array[cursor];
	new_value = value;
	
	//DRAW!
	initialize_textures();
	
	
	
	return 1; //success
}

void draw_sudoku() {
	int size = my_sudoku->size, square = sqrt(size);
	int i=0, row=0, col=0, val=0;
	int x=0, y=0, offset = 0;
	
	
	
	
	for (i=0; i < (size*size); i++) {
		row = i % size;
		col = i / size;
		x = row * 25; y = col * 25; 
		//if (row % square) x+=5;
		//if (col % square) y+=5;
		x += offset; 
		val = my_sudoku->sudoku_array[i];
		
		if (my_sudoku->edit_array[i]) { //draw mutable block
			sf2d_draw_texture_part(mut_numbers, x, y, val*25, 0, 25, 25);
			sf2d_draw_rectangle(230+(row*10), 70+(col*10), 10, 10, RGBA8(0x00, 0x00, 0xFF, 0xFF));
		} else { //else draw immutable block
			sf2d_draw_texture_part(immut_numbers, x, y, val*25, 0, 25, 25);
			//sf2d_draw_rectangle(230+(row*10), 70+(col*10), 10, 10, RGBA8(0xFF, 0xFF, 0xFF, 0xFF));
		}
		row++;
	} 
}

//Draw the current static state
void draw_frame() {
//draw bg
//draw sudoku_puzzle - check for mutable
//draw selector
//draw victory box

	sf2d_start_frame(GFX_TOP, GFX_LEFT); //FRAME BEGIN
	sf2d_draw_texture(bg, 0, 0);
    draw_sudoku();
	sf2d_draw_texture(selector, cursor%my_sudoku->size * 25, cursor/my_sudoku->size * 25);
	
	if (check_all(my_sudoku)) {
		sf2d_draw_rectangle(390, 230, 10, 10, RGBA8(0xFF, 0xFF, 0xFF, 0xFF)); //draw victory box
	} else {
		sf2d_draw_rectangle(390, 230, 10, 10, RGBA8(0x00, 0xFF, 0xFF, 0xFF)); //draw defeata
	}
			
    sf2d_end_frame(); //FRAME END

}


//takes keys_down and all that
int check_input() {

	
	if (kDown & KEY_A) new_value = mod(my_sudoku->sudoku_array[cursor]+1, my_sudoku->size+1);
	else if (kDown & KEY_B) new_value = mod(my_sudoku->sudoku_array[cursor]-1, my_sudoku->size+1);
		
	else if (kDown & KEY_DOWN) cursor = mod((cursor + SU_SIZE), (SU_SIZE*SU_SIZE));
	else if (kDown & KEY_UP) cursor = mod((cursor - SU_SIZE), (SU_SIZE*SU_SIZE));
	else if (kDown & KEY_LEFT) cursor = mod((cursor - 1), (SU_SIZE*SU_SIZE));
	else if (kDown & KEY_RIGHT) cursor = mod((cursor + 1), (SU_SIZE*SU_SIZE));
		
	
	return 1;
}

void update_game() {	
	
	value = my_sudoku->sudoku_array[cursor];
	new_value = value;
	check_input();
	if (new_value != value && my_sudoku->edit_array[cursor] == 1) {
		my_sudoku->sudoku_array[cursor] = new_value;
	}
	
	draw_frame();
	
	
	
	
	

}




int main()
{
	initialize_game(SU_SIZE, SU_RAND);
	
	int flip = 0;
    while (aptMainLoop()) {
	
		hidScanInput();
		kDown = hidKeysDown();
		if (kDown & KEY_START) break;
		if (kDown & KEY_SELECT) break;
	
	
		flip = 1-flip;
		update_game();
		
 
        
 
      
            
        
 
        sf2d_swapbuffers();
    }

 
    sf2d_fini();
    return 0;
}

