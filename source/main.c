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



//Some globals for easy modifications
#define SU_SIZE 9
#define SU_RAND 99





int main()
{
	SudokuControl s_control = initialize_game(SU_SIZE, SU_RAND);

    while (aptMainLoop()) {
		update_state(s_control);
		
        //sf2d_swapbuffers();  //ZZZ Probably need this somewhere in gfx
		if (s_control->exit_flag) break;
    }

 
    sf2d_fini();
    return 0;
}

