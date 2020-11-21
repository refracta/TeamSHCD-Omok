/**
  @file gamerenderer.c
  @brief 게임 렌더러
*/
#include <stdio.h>
#include "inc/gamerenderer.h"
#include "inc/gamecore.h"
#include <string.h>
#include <malloc.h>
#include "inc/consoleutils.h"
#include <wchar.h>
#include <stdbool.h>

/**
* @brief GridRenderData 구조체를 동적 할당하여 반환합니다.
* @param width 격자의 가로 크기
* @param height 격자의 세로 크기
*/
GridRenderData * malloc_grd(int width, int height) {
	GridRenderData* grd = (GridRenderData*)malloc(sizeof(GridRenderData));
	grd->width = width;
	grd->height = height;
	char ** grid = generate_grid(width, height);
	grd->grid = grid;
	short ** stone_colors = (short**)malloc_double_pointer(sizeof(short), width, height);
	grd->stone_colors = stone_colors;
	return grd;
}

/**
* @brief 동적할당된 GridRenderData 구조체의 메모리를 해제합니다.
* @param grd 격자 렌더 데이터
*/
void free_grd(GridRenderData* grd) {
	free_double_pointer(grd->grid, grd->width);
	free_double_pointer(grd->grid, grd->width);
	free(grd);
}

/**
* @brief SimpleGlyph To RenderGlyph, SimpleGlyph를 RenderGlyph로 변환합니다.
* @param sg SimpleGlyph
* @return RenderGlyph
*/
wchar_t* sg2rg(char sg) {
	switch (sg) {
	case SG_BLACK:
		return RG_BLACK;
	case SG_WHITE:
		return RG_WHITE;
	default:
		return NULL;
	}
}

/**
* @brief 돌이 있는 배열을 입력받아서 격자와 함께 string으로 반환해주는 함수
* @param grd 격자 렌더 데이터
*/
wchar_t* generate_grid_string(GridRenderData * grd)
{
	wchar_t* grid_string = (wchar_t*)calloc(grd->width * grd->height * 2 * sizeof(wchar_t) + 1, sizeof(wchar_t));

	const int last_w_index = grd->width - 1;
	const int last_h_index = grd->height - 1;
	const int first_index = 0;

	for (int i = 0; i < grd->height; i++)
	{
		for (int j = 0; j < grd->width; j++)
		{
			/* 돌은 렌더링 하지 말고 격자만 렌더링 후 Coloring stone한다.
			char glyph = grid[j][i];
			if (glyph != SG_EMPTY) {
				bool is_need_padding = !(j == 0 || grid[j - 1][i] != SG_EMPTY);
				if (is_need_padding) {
					wcscat(grid_string, L" ");
				}
				wcscat(grid_string, sg2rg(glyph));
				continue;
			}
			*/
			if (i == first_index && j == first_index)
				wcscat(grid_string, RG_GRID_TYPE_7); //좌상단 격자
			else if (i == first_index && j == last_w_index)
				wcscat(grid_string, RG_GRID_TYPE_9); //우상단 격자
			else if (i == first_index)
				wcscat(grid_string, RG_GRID_TYPE_8); //상단 격자
			else if (i != last_h_index && j == first_index)
				wcscat(grid_string, RG_GRID_TYPE_4); //좌측 격자
			else if (i != last_h_index && j == last_w_index)
				wcscat(grid_string, RG_GRID_TYPE_6); //우측 격자
			else if (i == last_h_index && j == first_index)
				wcscat(grid_string, RG_GRID_TYPE_1); //좌하단 격자
			else if (i == last_h_index && j == last_w_index)
				wcscat(grid_string, RG_GRID_TYPE_3); //우하단 격자
			else if (i == last_h_index)
				wcscat(grid_string, RG_GRID_TYPE_2);//하단 격자
			else
				wcscat(grid_string, RG_GRID_TYPE_5); //모서리가 아닌 격자
			if ((j == last_w_index))
				continue;
			wcscat(grid_string, RG_GRID_TYPE_H); //격자가 위아래로 길어져서 가로문자 하나를 넣어 정사각형으로 보이게 함
		}
		wcscat(grid_string, L" \n");
	}

	return grid_string;
}



/**
* @brief 돌이 있는 배열을 입력받아서 돌과 함께 색상을 입혀 지정된 오프셋 위치에 출력하는 함수
* @param grd 격자 렌더 데이터
*/
void draw_grid(GridRenderData* grd)
{
	short origin_color = get_print_color();
	set_print_color(grd->line_color);
	wchar_t* grid_string = generate_grid_string(grd);
	xywprintf(grd->x, grd->y, grid_string);
	free(grid_string);

	for (int i = 0; i < grd->height; i++)
	{
		for (int j = 0; j < grd->width; j++)
		{
			char glyph = grd->grid[j][i];
			if (glyph != SG_EMPTY) {
				coloring_stone(grd->x, grd->y, j, i, grd->grid[j][i], grd->stone_colors[j][i]);
			}
		}
	}
	set_print_color(origin_color);
}


/**
* @brief b혹은 w를 입력받아서 지정된 위치에 색상과 함께 돌을 출력한다.
* @param offset_x 콘솔 상에서 x좌표 오프셋 (콘솔의 왼쪽에서 격자의 시작점까지)
* @param offset_y 콘솔 상에서 y좌표 오프셋 (콘솔의 위쪽에서 격자의 시작점까지)
* @param x 출력을 시작할 격자의 x좌표
* @param y 출력을 시작할 격자의 y좌표
* @param glyph SG (b 혹은 w)
* @param color 돌 색상
*/
void coloring_stone(int offset_x, int offset_y, int x, int y, char glyph, short color)
{
	short origin_color = get_print_color();

	set_print_color(color);
	xywprintf(x * 2 + offset_x, y + offset_y, glyph == SG_BLACK ? RG_BLACK : (glyph == SG_WHITE ? RG_WHITE : L"X"));

	set_print_color(origin_color);
}