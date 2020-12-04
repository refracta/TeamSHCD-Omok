/**
  @file gridrenderer.c
  @brief 격자 관련 렌더링 함수들이 구현된 소스 파일
*/

#include "gridrenderer.h"

/**
* @brief GridRenderData 구조체를 동적 할당하여 반환합니다.
* @param width 격자의 가로 크기
* @param height 격자의 세로 크기
*/
GridRenderData *malloc_grd(int width, int height)
{
    GridRenderData *grd = (GridRenderData *) malloc(sizeof(GridRenderData));
    grd->width = width;
    grd->height = height;
    grd->cursor_x = width / 2;
    grd->cursor_y = height / 2;
    char **grid = generate_grid(width, height);
    grd->grid = grid;
    short **stone_colors = (short **) malloc_double_pointer(sizeof(short), width, height);
    grd->stone_colors = stone_colors;
    return grd;
}

/**
* @brief 동적할당된 GridRenderData 구조체의 메모리를 해제합니다.
* @param grd 격자 렌더 데이터
*/
void free_grd(GridRenderData *grd)
{
    free_double_pointer(grd->stone_colors, grd->width);
    free_double_pointer(grd->grid, grd->width);
    free(grd);
}

/**
* @brief 돌이 있는 배열을 입력받아서 돌과 함께 색상을 입혀 지정된 오프셋 위치에 출력하는 함수
* @param grd 격자 렌더 데이터
*/
void draw_grid(GridRenderData *grd)
{
    short origin_color = get_print_color();

    const int last_w_index = grd->width - 1;
    const int last_h_index = grd->height - 1;
    const int first_index = 0;


    for (int i = 0; i < grd->height; i++)
    {
        for (int j = 0; j < grd->width; j++)
        {
            char glyph = grd->grid[j][i];
            if (glyph != SG_EMPTY)
            {
                bool is_need_padding = !(j == 0 || grd->grid[j - 1][i] != SG_EMPTY);
                if (is_need_padding)
                {
                    xywprintf(grd->x + j * 2, grd->y + i, L" ", SG2RG(glyph));
                }
                set_print_color(grd->stone_colors[j][i]);
                xywprintf(grd->x + j * 2, grd->y + i, SG2RG(glyph));
                set_print_color(origin_color);
                continue;
            }

            set_print_color(grd->line_color);
            if (i == first_index && j == first_index)
            {
                xywprintf(grd->x + j * 2, grd->y + i, RG_GRID_TYPE_7);
            }
            else if (i == first_index && j == last_w_index)
            {
                xywprintf(grd->x + j * 2, grd->y + i, RG_GRID_TYPE_9);
            }
            else if (i == first_index)
            {
                xywprintf(grd->x + j * 2, grd->y + i, RG_GRID_TYPE_8);
            }
            else if (i != last_h_index && j == first_index)
            {
                xywprintf(grd->x + j * 2, grd->y + i, RG_GRID_TYPE_4);
            }
            else if (i != last_h_index && j == last_w_index)
            {
                xywprintf(grd->x + j * 2, grd->y + i, RG_GRID_TYPE_6);
            }
            else if (i == last_h_index && j == first_index)
            {
                xywprintf(grd->x + j * 2, grd->y + i, RG_GRID_TYPE_1);
            }
            else if (i == last_h_index && j == last_w_index)
            {
                xywprintf(grd->x + j * 2, grd->y + i, RG_GRID_TYPE_3);
            }
            else if (i == last_h_index)
            {
                xywprintf(grd->x + j * 2, grd->y + i, RG_GRID_TYPE_2);
            }
            else
            {
                xywprintf(grd->x + j * 2, grd->y + i, RG_GRID_TYPE_5);
            }
            if ((j == last_w_index))
            {
                wprintf(L" ");
                continue;
            }
            xywprintf(grd->x + j * 2 + 1, grd->y + i, L" ");
        }
        wprintf(L"\n");
    }

    set_print_color(origin_color);
}

/**
* @brief b혹은 w를 입력받아서 지정된 위치에 색상과 함께 돌을 출력한다.
* @param x 콘솔 상에서 x좌표 오프셋 (콘솔의 왼쪽에서 격자의 시작점까지)
* @param y 콘솔 상에서 y좌표 오프셋 (콘솔의 위쪽에서 격자의 시작점까지)
* @param cursor_x 출력을 시작할 격자의 x좌표
* @param cursor_y 출력을 시작할 격자의 y좌표
* @param glyph SG (b 혹은 w)
* @param color 돌 색상
*/
void coloring_stone(int x, int y, int cursor_x, int cursor_y, char glyph, short color)
{
    short origin_color = get_print_color();

    set_print_color(color);
    xywprintf(cursor_x * 2 + x, cursor_y + y, SG2RG(glyph));

    set_print_color(origin_color);
}