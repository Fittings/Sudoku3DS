#include <3ds.h>
#include <math.h>
#include "gfx_info.h"

void draw_sudoku(SudokuGFX s_gfx, int *sudoku_array, int *edit_array, int size, int x_offset, int y_offset, int cursor) {
	int i, square = sqrt(size);
	int row=0, col=0, val=0;
	int x=0, y=0;// offset = 0;
	int x_div_offset = 0;
	int y_div_offset = 0;

	for (i=0; i < (size*size); i++) {
		row = i % size;
		col = i / size;
		x = row * TILE_SIZE; y = col * TILE_SIZE;
		if (row % (square) == 0) x_div_offset = (row-1)*1;
		if (col % (square) == 0) y_div_offset = (col-1)*1;
		x += (x_offset+x_div_offset); y += (y_offset+y_div_offset);
		val = sudoku_array[i];
		if (edit_array[i]) { //draw mutable block
			sf2d_draw_texture_part(s_gfx->mut_numbers, x, y, val*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
		} else { //else draw immutable block
			sf2d_draw_texture_part(s_gfx->immut_numbers, x, y, val*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
		}
		if (row == (cursor%size) && col == (cursor/size)) {//draw selector
			sf2d_draw_texture(s_gfx->selector, x, y);
		}
		row++;
	} 
}