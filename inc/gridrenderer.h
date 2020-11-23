#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include "gamecore.h"
#include "consoleutils.h"

#define RG_BLACK L"●"
#define RG_WHITE L"●"
#define RG_CURSOR L"◈"
#define RG_BANNED L"ⓧ"

#define RG_GRID_TYPE_1 L"└"
#define RG_GRID_TYPE_2 L"┴"
#define RG_GRID_TYPE_3 L"┘"
#define RG_GRID_TYPE_4 L"├"
#define RG_GRID_TYPE_5 L"┼"
#define RG_GRID_TYPE_6 L"┤"
#define RG_GRID_TYPE_7 L"┌"
#define RG_GRID_TYPE_8 L"┬"
#define RG_GRID_TYPE_9 L"┐"
#define RG_GRID_TYPE_H L"─"
#define RG_GRID_TYPE_V L"│"

#define SG2RG(sg)                     \
    (                                 \
        sg == SG_BLACK ? RG_BLACK :   \
        sg == SG_WHITE ? RG_WHITE :   \
        sg == SG_CURSOR ? RG_CURSOR : \
        sg == SG_BANNED ? RG_BANNED : \
        NULL                          \
    )

typedef struct
{
    int x;
    int y;
    int cursor_x;
    int cursor_y;
    char **grid;
    short **stone_colors;
    int width;
    int height;
    short line_color;
    short black_color;
    short white_color;
    short cursor_color;
    short banned_color;
} GridRenderData;

GridRenderData *malloc_grd(int width, int height);

void free_grd(GridRenderData *grd);

void draw_grid(GridRenderData *grd);

wchar_t *generate_grid_string(GridRenderData *grd);

void coloring_stone(int x, int y, int cursor_x, int cursor_y, char glyph, short color);

#endif





