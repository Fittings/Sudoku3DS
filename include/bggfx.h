#ifndef BGGFX_H_
#define BGGFX_H_

#include <sf2d.h>
#include <sfil.h>

#include "gfx_info.h"
#include "bggfx.h"



//Screen resolutions
#define TOP_W 400
#define TOP_H 240
#define BOTTOM_W 320
#define BOTTOM_H 240

void draw_slide_background(SudokuGFX s_gfx, gfxScreen_t screen);

extern void draw_top_background(SudokuGFX s_gfx);
extern void draw_bottom_background(SudokuGFX s_gfx);

#endif