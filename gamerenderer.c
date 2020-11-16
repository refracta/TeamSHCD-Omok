#include <stdio.h>
#include "inc/gamerenderer.h"
#include "inc/gamecore.h"
#include "inc/consoleutils.h"

/**
* @brief 돌이 있는 배열을 입력받아서 격자와 함께 출력해주는 함수
* @param grid 돌 위치가 담긴 배열(13x13 격자, 흑돌은 'b', 백돌은 'w')
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
				printf("%s", RG_GRID_TYPE_7);//좌상단 격자
			else if (i == first_index && j == last_w_index)
				printf("%s", RG_GRID_TYPE_9);//우상단 격자
			else if (i == first_index)
				printf("%s", RG_GRID_TYPE_8);//상단 격자
			else if (i != last_h_index && j == first_index)
				printf("%s", RG_GRID_TYPE_4);//좌측 격자
			else if (i != last_h_index && j == last_w_index)
				printf("%s", RG_GRID_TYPE_6);//우측 격자
			else if (i == last_h_index && j == first_index)
				printf("%s", RG_GRID_TYPE_1);//좌하단 격자
			else if (i == last_h_index && j == last_w_index)
				printf("%s", RG_GRID_TYPE_3);//우하단 격자
			else if (i == last_h_index)
				printf("%s", RG_GRID_TYPE_2);//하단 격자
			else
				printf("%s", RG_GRID_TYPE_5); //모서리가 아닌 격자
			if (j != last_w_index)
				printf("%s", RG_GRID_TYPE_H); //격자가 위아래로 길어져서 가로문자 하나를 넣어 정사각형으로 보이게 함
		}
<<<<<<< Updated upstream
		printf("\n");
=======
		printf(" \n"); //���� ���� ©�� �ذ��� ���� ���� �� ����
>>>>>>> Stashed changes
	}

	//돌 놓기
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j] == 'b')
				xyprintf(j * 2, i, RG_BLACK); //까만돌은 속이 차있어서 왼쪽 격자 튀어나오는 부분을 해결 안해도 됨.
			else if (grid[i][j] == 'w')
			{
				if ((grid[i][j - 1] == 'w' || grid[i][j - 1] == 'b') || j == 0) //흰돌(비어있는 동그라미)에서 1. 바로 앞에 돌이 놓여있거나 2. 첫 열에 놓는 경우엔 격자버그 처리 안함
					xyprintf(j * 2, i, RG_WHITE);
				else
					xyprintf(j * 2 - 1, i, " " RG_WHITE); //나머지 경우엔, 한 칸 앞에서부터 [공백 + 돌]을 그린다.
			}
		}
	}
}