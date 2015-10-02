#ifndef STARTGFX_H_
#define STARTGFX_H_

#include <sf2d.h>
#include <sfil.h>
#include "sudokugfx.h"

//Screen resolutions
#define TOP_W 400
#define TOP_H 240
#define BOTTOM_W 320
#define BOTTOM_H 240
#define TILE_SIZE 25

extern void draw_start_gfx_top(SudokuGFX s_gfx);
extern void draw_start_gfx_bottom(SudokuGFX s_gfx);

#endif