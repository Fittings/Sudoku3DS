#include <stdlib.h> //malloc, rand
#include <stdio.h> //printf
#include <time.h> //time
#include <math.h> //sqrt

#include "sudoku.h"

//Structure for a unknown NxN sized array. Where N = size
struct _Sudoku {
	int size;
	int* sudoku_array;

};

//Creates an empty representation of Sudoku of size n
Sudoku sudoku_new(int n) {
	Sudoku my_sudoku = malloc(sizeof my_sudoku); //this might be wrong? *my_sudoku instead??
	my_sudoku->size = n;
	my_sudoku->sudoku_array = malloc(n * sizeof my_sudoku->sudoku_array[0]);
	return my_sudoku;
}

void sudoku_free(Sudoku sudoku) {
	free(sudoku->sudoku_array);
	sudoku->sudoku_array = 0; //optional
}


//This is only for my own testing sake
void sudoku_print(Sudoku sudoku) {
	int size = sudoku->size, box = sqrt(size);
	int i;
	for (i=0; i < (size * size); i++) {
		if (i % box == 0) {
			printf("Hello WOrld");
		}
		printf("%i ", sudoku->sudoku_array[i]); 
	}
}


//Deletes values of the sudoku puzzle with a percentage chance
extern void sudoku_delete_space(Sudoku sudoku, int percentage) {
	srand(time(NULL));
	int i;
	for (i=0; i < sudoku->size; i++) {
		if (rand() % 101 >= percentage) { 
			sudoku->sudoku_array[i] = 0;
		}
	}

}



//Flips a compeleted sudoku a random amounts of times around different axes
//http://dryicons.com/blog/2009/08/14/a-simple-algorithm-for-generating-sudoku-puzzles/
void sudoku_transform(Sudoku sudoku){
	srand(time(NULL));
	int swap_chance = 95;
	while (rand() % 101 < swap_chance) {
		sudoku_flip_vert(sudoku);
	}
	while (rand() % 101 < swap_chance) {
		sudoku_flip_vert(sudoku);
	}
	while (rand() % 101 < swap_chance) {
		sudoku_flip_vert(sudoku);
	}
	while (rand() % 101 < swap_chance) {
		sudoku_flip_vert(sudoku);
	}
}



void sudoku_flip_vert(Sudoku sudoku) {
	int size = sudoku->size;
	int i, box = sqrt(size);
	for (i=0; i < (size * size); i++) {
		if ( (i % size) < (box+1) ) {
			int tmp = sudoku->sudoku_array[i];
			int div_siz = i / size;
			int tmpIx = (size * div_siz + div_siz - 1) - (i - (size * div_siz));
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
















