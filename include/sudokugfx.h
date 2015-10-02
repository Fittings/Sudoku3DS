#ifndef SUDOKUGFX_H_
#define SUDOKUGFX_H_

#include <sf2d.h>
#include <sfil.h>
#include "gfx_info.h"


extern void draw_sudoku(SudokuGFX s_gfx, int *sudoku_array, int *edit_array, int size, int x_offset, int y_offset, int cursor);

#endif