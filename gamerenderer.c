#include <stdio.h>

void render_grid(char[][13]);
void play_put_stone_animation(char grid[][13], int stone_x, int stone_y);

/**
* @brief 돌이 있는 배열을 입력받아서 격자와 함께 출력해주는 함수
* @param grid[][13] 돌 위치가 담긴 배열(13x13 격자, 흑돌은 'b', 백돌은 'w')
* @return 없음.
*/
void render_grid(char grid[][13])
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (grid[i][j] == 'b')
				printf("●"); //모서리가 아닌 격자
			else if (grid[i][j] == 'w')
				printf("○"); //모서리가 아닌 격자
			else
			{
				if (i == 0 && j == 0) //좌상단 격자
					printf("┌");
				else if (i == 0 && j == 12) //우상단 격자
					printf("┐");
				else if (i == 0) //상단 격자
					printf("┬");
				else if (i != 12 && j == 0) //좌측 격자
					printf("├");
				else if (i != 12 && j == 12) //우측 격자
					printf("┤");
				else if (i == 12 && j == 0) //좌하단 격자
					printf("└");
				else if (i == 12 && j == 12) //우하단 격자
					printf("┘");
				else if (i == 12) //하단 격자
					printf("┴");
				else
				{
					printf("┼"); //모서리가 아닌 격자
				}
			}
			if (grid[i][j] != 'b' && grid[i][j] != 'w' && j != 12) //격자가 위아래로 길어져서 가로문자 하나를 넣어 정사각형으로 보이게 함.
			{
				printf("─");
			}
		}
		printf("\n");
	}
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