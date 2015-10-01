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

extern Sudoku sudoku_new(int n);
extern void sudoku_free(Sudoku sudoku);

extern void sudoku_print(Sudoku sudoku);


extern void sudoku_default(Sudoku sudoku);
extern void sudoku_delete_space(Sudoku sudoku, int percentage);

extern void sudoku_transform(Sudoku sudoku);
extern void sudoku_flip_box_rows(Sudoku sudoku);
extern void sudoku_swap_row(Sudoku sudoku, int row1, int row2);
extern void sudoku_swap_col(Sudoku sudoku, int row1, int row2);
extern void sudoku_flip_vert(Sudoku sudoku);
extern void sudoku_flip_hori(Sudoku sudoku);
extern void sudoku_flip_dia1(Sudoku sudoku);
extern void sudoku_flip_dia2(Sudoku sudoku);

extern int check_horizontals(Sudoku sudoku);
extern int check_verticals(Sudoku sudoku);
extern int check_boxes(Sudoku sudoku);
extern int check_all(Sudoku sudoku);




#endif
