#ifndef GAMEVIEWRENDERER_H
#define GAMEVIEWRENDERER_H

#include <stdlib.h>
#include <wchar.h>
#include "gridrenderer.h"
#include "interfacerenderer.h"
#include "memoryutils.h"

void draw_game_rule();

void draw_game_message(wchar_t list[8][BUFSIZ]);

void draw_select_stone(GridRenderData *grd);

#endif