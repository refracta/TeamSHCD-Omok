/**
 @file gameviewrenderer.h
 @brief gameviewrenderer의 헤더 파일
*/
#ifndef GAMEVIEWRENDERER_H
#define GAMEVIEWRENDERER_H

#include <stdlib.h>
#include <wchar.h>
#include "gridrenderer.h"
#include "interfacerenderer.h"
#include "memoryutils.h"

void draw_game_rule(int victory_condition, wchar_t *time_limit);

void draw_game_message(wchar_t list[8][BUFSIZ]);

void draw_select_stone(GridRenderData *grd);

#endif