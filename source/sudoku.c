#include "sudoku.h"

//Creates an empty representation of Sudoku of size n
Sudoku sudoku_new(int n, int seed) {
	Sudoku my_sudoku = malloc(sizeof *my_sudoku);
	if (my_sudoku == NULL) { //Safety
		free(my_sudoku);
		return NULL;
	}
	my_sudoku->size = n;
	my_sudoku->sudoku_array = malloc(n * n * sizeof my_sudoku->sudoku_array[0]);
	my_sudoku->edit_array = malloc(n * n * sizeof my_sudoku->edit_array[0]);
	if (my_sudoku->sudoku_array == NULL || my_sudoku->edit_array == NULL) { //Safety
		return NULL;
	}
	
	memset(my_sudoku->edit_array, 0, my_sudoku->size * sizeof(int));
	memset(my_sudoku->sudoku_array, 0, my_sudoku->size * sizeof(int));
	//srand(time(NULL));
	srand(seed);
	return my_sudoku;
}



//Creates a unique set-up initially
Sudoku sudoku_unique_setup(int n, int percentage, int seed) {
	Sudoku u_sudoku = sudoku_new(n, seed);
	sudoku_default(u_sudoku);
	sudoku_transform(u_sudoku);
	sudoku_delete_space(u_sudoku, percentage);
	return u_sudoku;
}


//Frees sudoku
void sudoku_free(Sudoku sudoku) {
	if (sudoku != NULL) {  //Safety
		free(sudoku->sudoku_array);
		free(sudoku->edit_array);
		sudoku->sudoku_array = 0; //optional
		free(sudoku);
	}
}

void sudoku_set_arrays_to_zero(Sudoku sudoku) {
	int i, size = sudoku->size;
	for (i=0; i < (size*size); i++) {
		sudoku->edit_array[i] = 0;
		sudoku->sudoku_array[i] = 0;
	}
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
	//srand(time(NULL));
	int array_size = sudoku->size * sudoku->size;
	int i;
	for (i=0; i < array_size; i++) {
		if (rand() % 101 >= percentage) { 
			sudoku->edit_array[i] = 1; //Editable spot
			sudoku->sudoku_array[i] = 0;
		}
	}

}

//Re makes the board to a new state
void sudoku_remake(Sudoku sudoku, int percentage) {
	//reset edit_array
	sudoku_set_arrays_to_zero(sudoku);
	sudoku_default(sudoku);
	sudoku_transform(sudoku);
	sudoku_delete_space(sudoku, percentage);
	//transform
	//delete
}

//This resets all edited spots back to empty.
void sudoku_reset(Sudoku sudoku) {
	int i, size = sudoku->size;
	for (i=0; i < (size*size); i++) {
		if (sudoku->edit_array[i] == 1) {
			sudoku->sudoku_array[i] = 0;
		}
	}
}



//Flips a compeleted sudoku a random amounts of times around different axes
//http://dryicons.com/blog/2009/08/14/a-simple-algorithm-for-generating-sudoku-puzzles/
void sudoku_transform(Sudoku sudoku) {
	//srand(time(NULL));
	int i = 0;
	while (i < 5000) { //Magic number, I know...
		i++;
		int val = rand_lim(150);
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
		} else if (100 <= 125) {
			sudoku_flip_box_rows(sudoku);
		} else if (125 < 150) {
			sudoku_flip_box_rows(sudoku);
		} else if (150 < 175) {
			sudoku_flip_rowbox(sudoku);
		} else if (175 < 200) {
			sudoku_flip_colbox(sudoku);
		}
		
	}

}


//Flips rows randomly in each small box
void sudoku_flip_box_rows(Sudoku sudoku) {
	int i, row,  size = sudoku->size, div_size=sqrt(size);
	int old_div=0, new_div=div_size;
	for (i=0; i < (size*size); i+=size) {
		row = i/size;
		while (80 > rand_lim(100)) { //Keep swapping with 80% chance
			int row1 = old_div + rand_lim(div_size-1); 
			int row2 = old_div + rand_lim(div_size-1);
			sudoku_swap_row(sudoku, row1, row2);
		}
		
		if ((row % (div_size) == 0) && (row != 0)) { //Entered a new box. Re-set boundaries.
			old_div = new_div;
			new_div += div_size;
		}
	}	
}
//Swaps columns randomly within a box
void sudoku_flip_box_cols(Sudoku sudoku) {
	int i, col,  size = sudoku->size, div_size=sqrt(size);
	int old_div=0, new_div=div_size;
	for (i=0; i < size; i++) {
		col = i % size;
		while (80 > rand_lim(100)) { //Keep swapping with 70% chance
			int col1 = old_div + rand_lim(div_size-1); 
			int col2 = old_div + rand_lim(div_size-1);
			sudoku_swap_col(sudoku, col1, col2);
		}
		
		if ((col % (div_size) == 0) && (col != 0)) { //Entered a new box. Re-set boundaries.
			old_div = new_div;
			new_div += div_size;
		}
	}
}




//Randomly swaps a row of boxes.
void sudoku_flip_rowbox(Sudoku sudoku) {
	int i = 0, div_size = sqrt(sudoku->size);
	for (i=0; i < div_size; i++) {
		while (80 > rand_lim(100)) {
			int brow1 = rand_lim(div_size-1);
			int brow2 = rand_lim(div_size-1);
			sudoku_swap_brow(sudoku, brow1, brow2);
		}
	}
}

//Randomly swaps a column of boxes				//ZZZThis could easily be combined into one function with a toggle parameter.
void sudoku_flip_colbox(Sudoku sudoku) {
	int i = 0, div_size = sqrt(sudoku->size);
	for (i=0; i < div_size; i++) {
		while (80 > rand_lim(100)) {
			int bcol1 = rand_lim(div_size-1);
			int bcol2 = rand_lim(div_size-1);
			sudoku_swap_bcol(sudoku, bcol1, bcol2);
		}
	}
}

//This swaps the rows of box1 with the rows of box2.
void sudoku_swap_brow(Sudoku sudoku, int brow1, int brow2) {
	int size = sudoku->size, div_size = sqrt(size);
	int i = brow1 * (div_size * size); int j = brow2 * (div_size * size);
	if (brow1 == brow2) return;
	int difference = j-i;
	int max = i + (div_size*size);
	//ZZZprintf("diff %i, max: %i\n", difference, max);
	for (i=i; i < max; i++) {
		int temp = sudoku->sudoku_array[i];
		//ZZZprintf("swapping %i and %i\n", i, i+difference);
		sudoku->sudoku_array[i] = sudoku->sudoku_array[i+difference];
		sudoku->sudoku_array[i+difference] = temp;
	}
}

//This swaps the columns of box1 with the columns of box2
void sudoku_swap_bcol(Sudoku sudoku, int bcol1, int bcol2) {
	if (bcol1 == bcol2) return; 
	int i, size = sudoku->size, div_size = sqrt(size);
	if (bcol1 >= sqrt(size) || bcol2 >= sqrt(size)) return;
	int col1 = bcol1 * div_size, col2 = bcol2 * div_size;
	int difference = col2-col1;
	int temp, offset=0;
	for (offset=0; offset < div_size; offset++) {
		for (i=col1; i < (size*size); i+=size) {
			temp = sudoku->sudoku_array[i+offset];
			sudoku->sudoku_array[i+offset] = sudoku->sudoku_array[i+difference+offset];
			sudoku->sudoku_array[i+difference+offset] = temp;
		}
	}
	
}



	
//This swaps rows. Intended to be used for the row flipping function.
void sudoku_swap_row(Sudoku sudoku, int row1, int row2) {
	if (row1 == row2) return;
	int i = row1 * sudoku->size, j = row2 * sudoku->size;
	int difference = j-i;
	int temp;
	int row_end = i +sudoku->size;
	for (i=i;i < row_end; i++) {
		temp = sudoku->sudoku_array[i];
		sudoku->sudoku_array[i] = sudoku->sudoku_array[i+difference];
		sudoku->sudoku_array[i+difference] = temp;
	}
}





//this swaps columns. Intended to be used for the column flipping function.
void sudoku_swap_col(Sudoku sudoku, int col1, int col2) {
	if (col1 == col2) return; 
	int i, size = sudoku->size; 
	int difference = col2-col1;
	int temp;
	for (i=col1; i < (size*size); i+=size) {
		temp = sudoku->sudoku_array[i];
		sudoku->sudoku_array[i] = sudoku->sudoku_array[i+difference];
		sudoku->sudoku_array[i+difference] = temp;
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


//Flips numbers across the diagonal 
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

//Flips numbers across the diagonal /
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
/*
	Sudoku my_sudoku = sudoku_new(9); //Create
	sudoku_default(my_sudoku); //Creates a non-unique generic sudoku
	//sudoku_print(my_sudoku); //Print
	sudoku_print(my_sudoku);
	printf("\nTransform\n");
	//sudoku_swap_brow(my_sudoku, 2, 1);
	//sudoku_flip_colbox(my_sudoku);
	sudoku_transform(my_sudoku); //Flips on many axes to create a unique sudoku
	
	sudoku_print(my_sudoku);
	
	printf("Hors?: %i\n", check_horizontals(my_sudoku));
	printf("Vert?: %i\n", check_verticals(my_sudoku));
	printf("Boxs?: %i\n", check_boxes(my_sudoku));
	//sudoku_print(my_sudoku);
	printf("\n");
	
	
	sudoku_delete_space(my_sudoku, 70); //Deletes spaces a random percentage
	sudoku_print(my_sudoku);
	printf("\n");
	int i;
	for (i=0; i < (my_sudoku->size * my_sudoku->size); i++) {
		if (my_sudoku->edit_array[i] == 1) {
			my_sudoku->sudoku_array[i] = 8;
		}
	}
	
	sudoku_print(my_sudoku);
	
	
	*/
	Sudoku my_sudoku = sudoku_unique_setup(9, 70, 42142114);
	//printf("reseting at 0, 1, 2\n");
	sudoku_reset(my_sudoku);
	sudoku_print(my_sudoku);
	
	
	
	printf("Free\n");
	sudoku_free(my_sudoku); 
	printf("Done\n");
}
#endif












