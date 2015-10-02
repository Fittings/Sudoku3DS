#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <stdlib.h> //malloc, rand
#include <string.h> //memset
#include <stdio.h> //printf
#include <time.h> //time
#include <math.h> //sqrt
#include "mylib.h" //rand



//Structure for a unknown NxN sized array. Where N = size
struct _Sudoku {
	int size;
	int *sudoku_array;
	int *edit_array;

};

typedef struct _Sudoku *Sudoku;

//Inits
extern Sudoku sudoku_new(int n, int seed);

extern Sudoku sudoku_unique_setup(int n, int percentage, int seed);
extern void sudoku_free(Sudoku sudoku);
extern void sudoku_set_arrays_to_zero(Sudoku sudoku);

//Other
extern void sudoku_print(Sudoku sudoku);

//Array Set-up
extern void sudoku_default(Sudoku sudoku);
extern void sudoku_delete_space(Sudoku sudoku, int percentage);
extern void sudoku_remake(Sudoku sudoku, int percentage);
extern void sudoku_reset(Sudoku sudoku);

//Transformations
extern void sudoku_transform(Sudoku sudoku);
extern void sudoku_flip_box_rows(Sudoku sudoku);
extern void sudoku_flip_box_cols(Sudoku sudoku);
extern void sudoku_flip_rowbox(Sudoku sudoku);
extern void sudoku_flip_colbox(Sudoku sudoku);
extern void sudoku_swap_brow(Sudoku sudoku, int brow1, int brow2);
extern void sudoku_swap_bcol(Sudoku sudoku, int bcol1, int bcol2);
extern void sudoku_swap_row(Sudoku sudoku, int row1, int row2);
extern void sudoku_swap_col(Sudoku sudoku, int row1, int row2);
extern void sudoku_flip_vert(Sudoku sudoku);
extern void sudoku_flip_hori(Sudoku sudoku);
extern void sudoku_flip_dia1(Sudoku sudoku);
extern void sudoku_flip_dia2(Sudoku sudoku);

//Checks
extern int check_horizontals(Sudoku sudoku);
extern int check_verticals(Sudoku sudoku);
extern int check_boxes(Sudoku sudoku);
extern int check_all(Sudoku sudoku);




#endif
