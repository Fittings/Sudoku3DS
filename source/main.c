#include <string.h>
#include <stdio.h> //printf

#include <3ds.h>



#include "sudoku.h"
#include "mylib.h" //mod




#include <sf2d.h>
#include <sfil.h>
#include "bg2_bin.h"

#define SU_SIZE 9
#define SU_RAND 50
int cursor;
int value;



int check_keys() {
	u32 kDown = hidKeysDown();
	if (kDown & KEY_A) printf("Hello World!");
	if (kDown & KEY_B) printf("Oh no!!!");
	if (kDown & KEY_START) return 1;
	if (kDown & KEY_SELECT) return 1;
	return 0;
}


int main()
{
	gfxInitDefault();
	consoleClear();

	consoleInit(GFX_TOP, NULL); // init console for top

	
	//consoleSelect(&bottomScreen);
	
	//Initialize my sudoku
	Sudoku my_sudoku = sudoku_new(SU_SIZE); 
	sudoku_default(my_sudoku); 
	//sudoku_transform(my_sudoku); 
	//sudoku_delete_space(my_sudoku, SU_RAND);
	//sudoku_print(my_sudoku);
	//sudoku_print(my_sudoku);

	cursor = 0;
	int value;
\
	int flip = 0;
	
	//Initialize my cursor
		
	sf2d_init();
	sf2d_texture *bg = sfil_load_PNG_buffer(bg2_bin, SF2D_PLACE_RAM);

	//gfxSet3D(true); // uncomment if using stereoscopic 3D

	// Main loop
	while (aptMainLoop()) {//this is a single frame
		flip = 1 - flip;
		gspWaitForVBlank(); //idk what this is.
		//sudoku_print(my_sudoku);
		hidScanInput();
		u32 kDown = hidKeysDown();
		value = my_sudoku->sudoku_array[cursor];
	
		//printf("\x1b[0;0HPress Start to exit.\n");
		// Your code goes here
		if (kDown & KEY_A) value = my_sudoku->sudoku_array[cursor] + 1;
		if (kDown & KEY_B) value = my_sudoku->sudoku_array[cursor] - 1;
		
		if (kDown & KEY_DOWN) cursor = mod((cursor + SU_SIZE), (SU_SIZE*SU_SIZE));
		if (kDown & KEY_UP) cursor = mod((cursor - SU_SIZE), (SU_SIZE*SU_SIZE));
		if (kDown & KEY_LEFT) cursor = mod((cursor - 1), (SU_SIZE*SU_SIZE));
		if (kDown & KEY_RIGHT) cursor = mod((cursor + 1), (SU_SIZE*SU_SIZE));
		
		if (kDown & KEY_START) break;
		if (kDown & KEY_SELECT) break;
		//cursor = cursor % (SU_SIZE * SU_SIZE);
		//int su2 = SU_SIZE * SU_SIZE;
		
		my_sudoku->sudoku_array[cursor] = mod(value, SU_SIZE);
		//printf("%i", cursor);
		//printf("\x1b[20;0Hi:%i, value=%i", cursor, value);
		//
		//printf("FPS: %i\n", (int) svcGetSystemTick());
		//drawFillRect( 59, 20, 260, 221, 19, 19, 19, bottomScreen)
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(bg, 0, 0);
		if (flip) {
			sf2d_draw_rectangle_rotate (0, 0, 10, 10, RGBA8(0xFF, 0xFF, 0x00, 0xFF), 0);
		} else {
			sf2d_draw_rectangle_rotate (0, 0, 10, 10, RGBA8(0xFF, 0xFF, 0xFF, 0xFF), 0);
		}
        sf2d_end_frame();


		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}

