#include <stdlib.h> //malloc, rand
#include <stdio.h> //printf
#include <time.h> //time
#include <math.h> //sqrt
#include "mylib.h" //rand
#include "sudoku.h"


//Structure for a unknown NxN sized array. Where N = size
struct _Sudoku {
	int size;
	int *sudoku_array;

};

//Creates an empty representation of Sudoku of size n
Sudoku sudoku_new(int n) {
	Sudoku my_sudoku = malloc(sizeof *my_sudoku); 
	my_sudoku->size = n;
	my_sudoku->sudoku_array = malloc(n * n * sizeof my_sudoku->sudoku_array[0]);
	//sudoku_empty(my_sudoku);
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
extern void sudoku_empty(Sudoku sudoku) {
	int i, size = sudoku->size;
	for (i=0; i < (size*size); i++) sudoku->sudoku_array[i] = 0;
}
extern void sudoku_default(Sudoku sudoku) {
	int i, size=sudoku->size;
	int divisor = sqrt(size); //used to know when we pass box dividers
	for (i=0; i < size; i++) { //initialize 0 to size-1
		sudoku->sudoku_array[i] = i+1;
	}
	int row_counter = 1;
	for (i=size; i < (size * size); i++) {
		if (i % size == 0) row_counter++;
		if ((row_counter-1) % divisor == 0) {
			int offset = ((row_counter-1) / divisor);
			sudoku->sudoku_array[i] = (sudoku->sudoku_array[(0 + i +(size-offset)) % (size)]);
		} else sudoku->sudoku_array[i] = ((sudoku->sudoku_array[i-size] + 2) % (9-1+1))+1;
	} //sudoku->sudoku_array[i] = (sudoku->sudoku_array[i-size]+divisor) % (size);

}


//Deletes values of the sudoku puzzle with a percentage chance
extern void sudoku_delete_space(Sudoku sudoku, int percentage) {
	srand(time(NULL));
	int array_size = sudoku->size * sudoku->size;
	int i;
	for (i=0; i < array_size; i++) {
		if (rand() % 101 >= percentage) { 
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
		//printf("%i ", val);
		if (0  <= val && val <  25) {
			//printf("flip vert\n");
			sudoku_flip_vert(sudoku);
		} else if (25 <= val && val <  50) {
			//printf("flip hori\n");
			sudoku_flip_hori(sudoku);
		}
		else if (50 <= val && val <  75) {
			//printf("flip dia1\n");
			sudoku_flip_dia1(sudoku);
		}
		else if (75 <= val && val < 100) {
			//printf("flip dia2\n");
			sudoku_flip_dia2(sudoku);
		}
		
	}

}



void sudoku_flip_vert(Sudoku sudoku) {
	int size = sudoku->size;
	int i, box = sqrt(size);
	for (i=0; i < (size * size); i++) {
		if ( (i % size) < (box+1) ) {
			int tmp = sudoku->sudoku_array[i];
			int div_siz = i / size;
			int tmpIx = ((size * div_siz) + size - 1) - (i - (size * div_siz));
			//printf("div_siz: %i, tmpIx: %i", div_siz, tmpIx);
			sudoku->sudoku_array[i] = sudoku->sudoku_array[tmpIx];
			sudoku->sudoku_array[tmpIx] = tmp;
		}
	}
	
}

void sudoku_flip_hori(Sudoku sudoku) {
	int size = sudoku->size;
	int i, box = sqrt(size);
	for (i=0; i < (size * size); i++) {
		if ( i/9 < box+1 ) {
			int tmp = sudoku->sudoku_array[i];
			int mod_siz = i % size;
			int div_siz = i / size;
			int tmpIx = mod_siz + (8 - div_siz) * size;
			sudoku->sudoku_array[i] = sudoku->sudoku_array[tmpIx];
			sudoku->sudoku_array[tmpIx] = tmp;
			
		}
	}
}



void sudoku_flip_dia1(Sudoku sudoku) {
	int i, size = sudoku->size;
	for (i=0; i < (size * size); i++) {
		if ((i / size + i % size) < 8) {
			int mod_siz = i % size;
			int div_siz = i / 9;
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
		if ( (i / 9) > (i % 9)) {
			int mod_siz = i % size;
			int div_siz = i / 9;
			int tmp = sudoku->sudoku_array[i];
			int tmpIx = div_siz + mod_siz * 9;
			sudoku->sudoku_array[i] = sudoku->sudoku_array[tmpIx];
			sudoku->sudoku_array[tmpIx] = tmp;
		}
	}
}
















