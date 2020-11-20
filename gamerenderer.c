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
* @param grid 돌 위치가 담긴 배열(격자, 흑돌은 SG_BLACK, 백돌은 SG_WHITE)
* @param width 격자의 가로 크기
* @param height 격자의 세로 크기
*/
wchar_t* generate_grid_string(char** grid, int width, int height)
{
	wchar_t* grid_string = (wchar_t*)calloc(width * height * 2 * sizeof(wchar_t) + 1, sizeof(wchar_t));

	const int last_w_index = width - 1;
	const int last_h_index = height - 1;
	const int first_index = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			char glyph = grid[j][i];
			if (glyph != SG_EMPTY) {
				bool is_need_padding = !(grid[j - 1][i] != SG_EMPTY || j == 0);
				if (is_need_padding) {
					wcscat(grid_string, L" ");
				}
				wcscat(grid_string, RG_BLACK);
				continue;
			}
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
			if ((j == last_w_index) || (grid[j + 1][i] != SG_EMPTY))
				continue;
			wcscat(grid_string, RG_GRID_TYPE_H); //격자가 위아래로 길어져서 가로문자 하나를 넣어 정사각형으로 보이게 함
		}
		wcscat(grid_string, L" \n");
	}

	return grid_string;
}


/**
* @brief 돌이 있는 배열을 입력받아서 돌과 함께 색상을 입혀 지정된 오프셋 위치에 출력하는 함수
* @param x 출력을 시작할 콘솔의 x좌표
* @param y 출력을 시작할 콘솔의 y좌표
* @param grid 돌 위치가 담긴 배열(격자, 흑돌은 SG_BLACK, 백돌은 SG_WHITE)
* @param stone_colors 각 위치마다 해당 돌의 색상이 담길 배열
* @param width 격자의 가로 크기
* @param height 격자의 세로 크기
* @param line_color 격자의 색상
*/
void draw_grid(int x, int y, char** grid, short** stone_colors, int width, int height, short line_color)
{
	short origin_color = get_print_color();
	set_print_color(line_color);
	xywprintf(x, y, generate_grid_string(grid, width, height));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			char glyph = grid[j][i];
			if (glyph != SG_EMPTY) {
				coloring_stone(x, y, j, i, grid[j][i], stone_colors[j][i]);
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