#ifndef GFX_H_
#define GFX_H_

#include <sf2d.h>
#include <sfil.h>

//Screen resolutions
#define TOP_W 400
#define TOP_H 240
#define BOTTOM_W 320
#define BOTTOM_H 240
#define TILE_SIZE 25



struct _SudokuGFX {
	sf2d_texture *bg1, *bg2, *immut_numbers, *mut_numbers, *selector, *icon, *sudoku3ds_text;
	
	int top_frame, bottom_frame, bg_count;
}; 
typedef struct _SudokuGFX *SudokuGFX; 




extern SudokuGFX SudokuGFX_init();
extern void sudoku_gfx_free(SudokuGFX s_gfx);

extern void init_background(SudokuGFX s_gfx);
extern void update_background_position(SudokuGFX s_gfx);

extern void draw_many_boxes(SudokuGFX s_gfx);

extern void draw_board();
extern void draw_top_background(SudokuGFX s_gfx);
extern void draw_bottom_background(SudokuGFX s_gfx);

extern void draw_victory(int victory_flag);
extern void draw_sudoku(SudokuGFX s_gfx, int *sudoku_array, int *edit_array, int size, int x_offset, int y_offset, int cursor);
//extern void draw_selector(SudokuGFX s_gfx, int cursor, int size, int x_offset, int y_offset);
extern void start_draw(SudokuGFX s_gfx, gfxScreen_t screen);
extern void end_draw();
extern void end(); //ZZZ consider refactoring this



#endif