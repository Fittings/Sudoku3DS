#include <stdlib.h> //malloc, rand
#include <string.h> //memset
#include <stdio.h> //printf
#include <time.h> //time
#include <math.h> //sqrt
#include "mylib.h" //rand
#include "sudoku.h"




//Creates an empty representation of Sudoku of size n
Sudoku sudoku_new(int n) {
	Sudoku my_sudoku = malloc(sizeof *my_sudoku); 
	my_sudoku->size = n;
	my_sudoku->sudoku_array = malloc(n * n * sizeof my_sudoku->sudoku_array[0]);
	my_sudoku->edit_array = malloc(n * n * sizeof my_sudoku->edit_array[0]);
	memset(my_sudoku->edit_array, 0, my_sudoku->size * sizeof(int));
	
	return my_sudoku;
}


void sudoku_free(Sudoku sudoku) {
	free(sudoku->sudoku_array);
	sudoku->sudoku_array = 0; //optional
}


//This is only for my own testing sake
void sudoku_print(Sudoku sudoku) {
	int size = sudoku->size;
	int i;
	for (i=0; i < (size * size); i++) {
		if (i % size == 0 && i!=0) {
			printf("\n");
		}
		printf("%i ", sudoku->sudoku_array[i]); 
	}
	printf("\n");
}


void sudoku_default(Sudoku sudoku) {
	int i, size=sudoku->size;
	int divisor = sqrt(size); //used to know when we pass box dividers
	for (i=0; i < size; i++) { //initialize 0 to size-1
		sudoku->sudoku_array[i] = i+1;
	}
	int row_counter = 1;
	for (i=size; i < (size * size); i++) {
		if (i % size == 0) 	row_counter++; //new row
		if ((row_counter-1) % divisor == 0) { //if on divisor+1 row
			int offset = ((row_counter-1) / divisor);
			sudoku->sudoku_array[i] = (sudoku->sudoku_array[(i-offset) % size]);
		} else sudoku->sudoku_array[i] = sudoku->sudoku_array[(i-(i%size))-size + ((i+divisor) % size)];
	} //sudoku->sudoku_array[i] = (sudoku->sudoku_array[i-size]+divisor) % (size);

}


//Deletes values of the sudoku puzzle with a percentage chance
void sudoku_delete_space(Sudoku sudoku, int percentage) {
	srand(time(NULL));
	int array_size = sudoku->size * sudoku->size;
	int i;
	for (i=0; i < array_size; i++) {
		if (rand() % 101 >= percentage) { 
			sudoku->edit_array[i] = 1; //Editable spot
			sudoku->sudoku_array[i] = 0;
		}
	}

}



//Flips a compeleted sudoku a random amounts of times around different axes
//http://dryicons.com/blog/2009/08/14/a-simple-algorithm-for-generating-sudoku-puzzles/
void sudoku_transform(Sudoku sudoku) {
	srand(time(NULL));
	int i = 0;
	while (i < 5000) { //Magic number, I know...
		i++;
		int val = rand_lim(100);
		if (0  <= val && val <  25) {
			sudoku_flip_vert(sudoku);
		} else if (25 <= val && val <  50) {
			sudoku_flip_hori(sudoku);
		}
		else if (50 <= val && val <  75) {
			sudoku_flip_dia1(sudoku);
		}
		else if (75 <= val && val < 100) {
			sudoku_flip_dia2(sudoku);
		}
		
	}

}



void sudoku_flip_vert(Sudoku sudoku) {
	int size = sudoku->size;
	int i; //box = sqrt(size);
	for (i=0; i < (size * size); i++) {
		if ( (i % size) < (size/2) ) { //if less than half, swap
			int tmp = sudoku->sudoku_array[i];
			int div_siz = i / size;
			int tmpIx = ((size * div_siz) + size - 1) - (i - (size * div_siz));
			sudoku->sudoku_array[i] = sudoku->sudoku_array[tmpIx];
			sudoku->sudoku_array[tmpIx] = tmp;
		}
	}
	
}

void sudoku_flip_hori(Sudoku sudoku) {
	int size = sudoku->size;
	int i;
	for (i=0; i < (size * size); i++) {
		if ( (i/size ) < (size/2) ) {
			int tmp = sudoku->sudoku_array[i];
			int mod_siz = i % size;
			int div_siz = i / size;
			int tmpIx = mod_siz + ((size-1) - div_siz) * size;
			sudoku->sudoku_array[i] = sudoku->sudoku_array[tmpIx];
			sudoku->sudoku_array[tmpIx] = tmp;
			
		}
	}
}



void sudoku_flip_dia1(Sudoku sudoku) {
	int i, size = sudoku->size;
	for (i=0; i < (size * size); i++) {
		if ((i / size + i % size) < (size-1)) {
			int mod_siz = i % size;
			int div_siz = i / size;
			int tmp = sudoku->sudoku_array[i];
			int tmpIx = (size-1 - mod_siz) * size + size-1 - div_siz;
			sudoku->sudoku_array[i] = sudoku->sudoku_array[tmpIx];
			sudoku->sudoku_array[tmpIx] = tmp;
			
		}
	}



}

void sudoku_flip_dia2(Sudoku sudoku) {
	int i, size = sudoku->size;
	for (i=0; i < (size * size); i++) {
		if ( (i / size) > (i % size)) {
			int mod_siz = i % size;
			int div_siz = i / size;
			int tmp = sudoku->sudoku_array[i];
			int tmpIx = div_siz + mod_siz * size;
			sudoku->sudoku_array[i] = sudoku->sudoku_array[tmpIx];
			sudoku->sudoku_array[tmpIx] = tmp;
		}
	}
}


//Checks every horizontal row for validity
int check_horizontals(Sudoku sudoku) {
	int size = sudoku->size, i;
	int valid_array[size];
	memset(valid_array, 0, size * sizeof(int)); //init all to 0
	for (i=0; i < (size * size); i++) {
		if (i % (size) == 0) memset(valid_array, 0, size * sizeof(int)); //New row, reset valids	
		if (sudoku->sudoku_array[i] == 0) return 0; //Value is incomplete. Fail
		if (valid_array[sudoku->sudoku_array[i]-1] == 1) { //value already exists on horizontal. Fail
			return 0; 
			}
		valid_array[sudoku->sudoku_array[i]-1] = 1;
	}
	return 1; //Every horizontal is fine. Pass
}

//Check every vertical row for validity.
int check_verticals(Sudoku sudoku) {
	int size = sudoku->size, i, j;
	int valid_array[size];
	memset(valid_array, 0, size * sizeof(int)); //init all to 0
	
	for (i=0; i < size; i++) { //i represents the column
		memset(valid_array, 0, size * sizeof(int));
		for (j=i+0; j < (size * size); j+=size){ //j is the offset for the column
			if (sudoku->sudoku_array[j] == 0) return 0; //Value is incomplete. Fail
			if (valid_array[sudoku->sudoku_array[j]-1] == 1) return 0;  //value already exists on vert. Fail
			valid_array[sudoku->sudoku_array[j]-1] = 1;
		} 
	}
	return 1; //Every vertical is fine. Pass
}

//Checks every box is valid
int check_boxes(Sudoku sudoku) {
	int i=0,k, size=sudoku->size, divisor=sqrt(size), curr_val;
	int valid_array[size];
	memset(valid_array, 0, size * sizeof(int)); //init all to 0
	
	while (i < (size * size)) { //Check i is inbounds
		for (k=0; k<divisor; k++) { //Inside the box, check the values of all values on the vertical
			curr_val = sudoku->sudoku_array[i + (k * size)]-1;
			if (curr_val == -1) return 0; //Value is incomplete. Fail
			if (valid_array[curr_val] == 1) {
				return 0; //value already exists in box. Fail
			}
			valid_array[curr_val] = 1; //Value doesn't exist. Add to valid_array
		}
		i++;
		if (i % size == 0) { //end of row
			memset(valid_array, 0, size * sizeof(int));
			i += (size * (divisor-1)); //skip to the next vertical block 
		} else if (i % divisor == 0) { //new hori
			memset(valid_array, 0, size * sizeof(int));
		}
	}
	return 1; //Every Box is fine. Pass
}

int check_all(Sudoku sudoku) {
	if (check_horizontals(sudoku) && check_verticals(sudoku) && check_boxes(sudoku)) return 1;
	return 0;
}



//Basic testing code for each function. Define SUDOKU_TEST at compile time to run. (See my test scripts)
#ifdef SUDOKU_TEST
int main(void) {
	Sudoku my_sudoku = sudoku_new(4); //Create
	sudoku_default(my_sudoku); //Creates a non-unique generic sudoku
	//sudoku_print(my_sudoku); //Print
	//printf("\nTransform\n");
	//sudoku_transform(my_sudoku); //Flips on many axes to create a unique sudoku
	my_sudoku->sudoku_array[0] = 0;//ZZZ TESTING
	//my_sudoku->sudoku_array[1] = 0;//ZZZ TESTING
	//my_sudoku->sudoku_array[9] = 1;
	sudoku_print(my_sudoku);
	
	printf("Hors?: %i\n", check_horizontals(my_sudoku));
	printf("Vert?: %i\n", check_verticals(my_sudoku));
	printf("Boxs?: %i\n", check_boxes(my_sudoku));
	//sudoku_print(my_sudoku);
	printf("\n");
	
	
	//sudoku_delete_space(my_sudoku, 70); //Deletes spaces a random percentage
	//sudoku_print(my_sudoku);
	printf("Free\n");
	sudoku_free(my_sudoku); 
	printf("Done\n");
}
#endif












