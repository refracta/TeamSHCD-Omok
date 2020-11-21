#ifndef __GAMERENDERER_H__
#define __GAMERENDERER_H__

typedef struct {
    int x;
    int y;
    int cursor_x;
    int cursor_y;
    char** grid;
    short** stone_colors;
    int width;
    int height;
    short line_color;
    short black_color;
    short white_color;
    short cursor_color;
    short banned_color;
} GridRenderData;
#endif

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

#include <wchar.h>

GridRenderData* malloc_grd(int width, int height);
void free_grd(GridRenderData* grd);
wchar_t* generate_grid_string(GridRenderData *);
void draw_grid(GridRenderData *);
void coloring_stone(int offset_x, int offset_y, int x, int y, char glyph, short color);