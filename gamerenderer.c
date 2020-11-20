/**
  @file gamerenderer.c
  @brief 게임 렌더러
*/
#include <stdio.h>
#include "inc/gamerenderer.h"
#include <string.h>
#include <malloc.h>
#include "inc/consoleutils.h"

void render_grid(char** grid, int width, int height);
void play_put_stone_animation(char grid[][13], int stone_x, int stone_y);
char *generate_grid_string(char** grid, int width, int height);

/**
* @brief [Legacy] 돌이 있는 배열을 입력받아서 격자와 함께 출력해주는 함수
* @param grid 돌 위치가 담긴 배열(격자, 흑돌은 'b', 백돌은 'w')
* @param width 격자의 가로 크기
* @param height 격자의 세로 크기
*/
void render_grid(char** grid, int width, int height)
{
	const int last_w_index = width - 1;
	const int last_h_index = height - 1;
	const int first_index = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == first_index && j == first_index)
				wprintf(L"%s", RG_GRID_TYPE_7);//좌상단 격자
			else if (i == first_index && j == last_w_index)
				wprintf(L"%s", RG_GRID_TYPE_9);//우상단 격자
			else if (i == first_index)
				wprintf(L"%s", RG_GRID_TYPE_8);//상단 격자
			else if (i != last_h_index && j == first_index)
				wprintf(L"%s", RG_GRID_TYPE_4);//좌측 격자
			else if (i != last_h_index && j == last_w_index)
				wprintf(L"%s", RG_GRID_TYPE_6);//우측 격자
			else if (i == last_h_index && j == first_index)
				wprintf(L"%s", RG_GRID_TYPE_1);//좌하단 격자
			else if (i == last_h_index && j == last_w_index)
				wprintf(L"%s", RG_GRID_TYPE_3);//우하단 격자
			else if (i == last_h_index)
				wprintf(L"%s", RG_GRID_TYPE_2);//하단 격자
			else
				wprintf(L"%s", RG_GRID_TYPE_5); //모서리가 아닌 격자
			if (j != last_w_index)
				wprintf(L"%s", RG_GRID_TYPE_H); //격자가 위아래로 길어져서 가로문자 하나를 넣어 정사각형으로 보이게 함
		}
		wprintf(L" \n");
	}

	//돌 놓기
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j] == 'b')
				xywprintf(j * 2, i, RG_BLACK); //까만돌은 속이 차있어서 왼쪽 격자 튀어나오는 부분을 해결 안해도 됨.
			else if (grid[i][j] == 'w')
			{
				if ((grid[i][j - 1] == 'w' || grid[i][j - 1] == 'b') || j == 0) //흰돌(비어있는 동그라미)에서 1. 바로 앞에 돌이 놓여있거나 2. 첫 열에 놓는 경우엔 격자버그 처리 안함
					xywprintf(j * 2, i, RG_WHITE);
				else
					xywprintf(j * 2 - 1, i, L" " RG_WHITE); //나머지 경우엔, 한 칸 앞에서부터 [공백 + 돌]을 그린다.
			}
		}
	}
}

/**
* @brief 돌이 있는 배열을 입력받아서 격자와 함께 string으로 반환해주는 함수
* @param grid 돌 위치가 담긴 배열(격자, 흑돌은 'b', 백돌은 'w')
* @param width 격자의 가로 크기
* @param height 격자의 세로 크기
*/
char *generate_grid_string(char** grid, int width, int height)
{
	char* grid_string = (char *)calloc(width * height * 2 * 3 + 1, sizeof(char));

	//char* grid_string[1000] = { 0 };

	const int last_w_index = width - 1;
	const int last_h_index = height - 1;
	const int first_index = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j] == 'b')
			{
				if ((grid[i][j - 1] == 'w' || grid[i][j - 1] == 'b') || j == 0)
					strcat(grid_string, RG_BLACK);
				else
					strcat(grid_string, " " RG_BLACK);
				continue;
			}
			else if (grid[i][j] == 'w')
			{
				if ((grid[i][j - 1] == 'w' || grid[i][j - 1] == 'b') || j == 0)
					strcat(grid_string, RG_WHITE);
				else
					strcat(grid_string, " " RG_WHITE);
				continue;
			}
			if (i == first_index && j == first_index)
				strcat(grid_string, RG_GRID_TYPE_7); //좌상단 격자
			else if (i == first_index && j == last_w_index)
				strcat(grid_string, RG_GRID_TYPE_9); //우상단 격자
			else if (i == first_index)
				strcat(grid_string, RG_GRID_TYPE_8); //상단 격자
			else if (i != last_h_index && j == first_index)
				strcat(grid_string, RG_GRID_TYPE_4); //좌측 격자
			else if (i != last_h_index && j == last_w_index)
				strcat(grid_string, RG_GRID_TYPE_6); //우측 격자
			else if (i == last_h_index && j == first_index)
				strcat(grid_string, RG_GRID_TYPE_1); //좌하단 격자
			else if (i == last_h_index && j == last_w_index)
				strcat(grid_string, RG_GRID_TYPE_3); //우하단 격자
			else if (i == last_h_index)
				strcat(grid_string, RG_GRID_TYPE_2);//하단 격자
			else
				strcat(grid_string, RG_GRID_TYPE_5); //모서리가 아닌 격자
			if ((j == last_w_index) || ((grid[i][j+1] == 'w' || grid[i][j+1] == 'b')))
				continue;
			strcat(grid_string, RG_GRID_TYPE_H); //격자가 위아래로 길어져서 가로문자 하나를 넣어 정사각형으로 보이게 함
		}
		strcat(grid_string, " \n");
	}

	return grid_string;
}

/**
* @brief 돌이 있는 배열을 입력받아서 돌과 함께 색상을 입혀 지정된 오프셋 위치에 출력하는 함수
* @param x 출력을 시작할 콘솔의 x좌표
* @param y 출력을 시작할 콘솔의 y좌표
* @param grid 돌 위치가 담긴 배열(격자, 흑돌은 'b', 백돌은 'w')
* @param stone_colors 각 위치마다 해당 돌의 색상이 담길 배열
* @param width 격자의 가로 크기
* @param height 격자의 세로 크기
* @param line_color 격자의 색상
*/
void draw_grid(int x, int y, char** grid, short** stone_colors, int width, int height, short line_color)
{
	short origin_color = get_print_color();
	set_print_color(line_color);
	xyprintf(x, y, "%s", generate_grid_string(grid, width, height));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j] == 'b')
			{
				set_print_color(stone_colors[i][j]);
				xyprintf(j * 2 + x, i + y, RG_BLACK); //까만돌은 속이 차있어서 왼쪽 격자 튀어나오는 부분을 해결 안해도 됨.
			}
			else if (grid[i][j] == 'w')
			{
				if ((grid[i][j - 1] == 'w' || grid[i][j - 1] == 'b') || j == 0) //흰돌(비어있는 동그라미)에서 1. 바로 앞에 돌이 놓여있거나 2. 첫 열에 놓는 경우엔 격자버그 처리 안함
				{
					set_print_color(stone_colors[i][j]);
					xyprintf(j * 2 + x, i + y, RG_WHITE);
				}
				else
				{
					xyprintf(j * 2 - 1 + x, i + y, " " RG_WHITE); //나머지 경우엔, 한 칸 앞에서부터 [공백 + 돌]을 그린다.
					set_print_color(stone_colors[i][j]);
					xyprintf(j * 2 + x, i + y, RG_WHITE); //나머지 경우엔, 한 칸 앞에서부터 [공백 + 돌]을 그린다.
				}
			}
		}
	}

	set_print_color(origin_color);
	return;
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
	xyprintf(x * 2 + offset_x, y + offset_y, glyph == 'b' ? RG_BLACK : (glyph == 'w' ? RG_WHITE : "X"));

	set_print_color(origin_color);
	return;
}

/**
* @brief
* @param
* @return
*/
void play_put_stone_animation(char grid[][13], int stone_x, int stone_y)
{
	return;
}