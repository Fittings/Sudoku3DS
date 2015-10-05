#ifndef MAINMENUGFX_H_
#define MAINMENU_H_

#include <sf2d.h>
#include <sfil.h>
#include "gfx_info.h"


extern void draw_main_menu_bg(SudokuGFX s_gfx, gfxScreen_t screen);
extern void draw_main_menu_start(SudokuGFX s_gfx);
extern void draw_main_menu_logo(SudokuGFX s_gfx);
extern void draw_main_menu_difficulty(SudokuGFX s_gfx, int percentage);

#endif