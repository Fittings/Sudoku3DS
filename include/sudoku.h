#ifndef SUDOKU_H_
#define SUDOKU_H_



//Structure for a unknown NxN sized array. Where N = size
struct _Sudoku {
	int size;
	int *sudoku_array;

};

typedef struct _Sudoku *Sudoku;

extern Sudoku sudoku_new(int n);
extern void sudoku_free(Sudoku sudoku);

extern void sudoku_print(Sudoku sudoku);

extern void sudoku_empty(Sudoku sudoku);
extern void sudoku_default(Sudoku sudoku);
extern void sudoku_delete_space(Sudoku sudoku, int percentage);

extern void sudoku_transform(Sudoku sudoku);
extern void sudoku_flip_vert(Sudoku sudoku);
extern void sudoku_flip_hori(Sudoku sudoku);
extern void sudoku_flip_dia1(Sudoku sudoku);
extern void sudoku_flip_dia2(Sudoku sudoku);

extern int check_horizontals(Sudoku sudoku);




#endif
