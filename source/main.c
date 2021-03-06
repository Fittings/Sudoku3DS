#include <stdlib.h> //malloc


#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include <3ds.h>
#include "mylib.h" //mod


#include "sudokucontroller.h"


//ZZZ #include <sf2d.h>
//ZZZ #include <sfil.h>



//Some globals for easy modifications
#define SU_SIZE 9
#define SU_RAND 60





int main()
{
	SudokuControl s_control = initialize_game(SU_SIZE, SU_RAND);
	
	

	
    while (aptMainLoop()) { //Program loop
		control_game(s_control);
		if (s_control->exit_flag) break;
		
	}
	
	sudoku_control_free(s_control);
    
    return 0;
}

