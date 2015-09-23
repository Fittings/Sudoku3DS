#include <string.h>

#include <3ds.h>

#include "sudoku.h"

#define SU_SIZE 9
#define SU_RAND 70

int main()
{
	gfxInitDefault();
	
	//SOME TEST CODE
	Sudoku my_sudoku = sudoku_new(SU_SIZE);
	sudoku_transform(my_sudoku);
	sudoku_delete_space(my_sudoku, SU_RAND);
	sudoku_print(my_sudoku);
	sudoku_free(my_sudoku);
	

	//gfxSet3D(true); // uncomment if using stereoscopic 3D

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		// Your code goes here

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		// Example rendering code that displays a white pixel
		// Please note that the 3DS screens are sideways (thus 240x400 and 240x320)
		u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
		memset(fb, 0, 240*400*3);
		fb[3*(10+10*240)] = 0xFF;
		fb[3*(10+10*240)+1] = 0xFF;
		fb[3*(10+10*240)+2] = 0xFF;

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
