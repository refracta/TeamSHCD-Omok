/**
  @file gamecore.c
  @brief 게임 코어
*/
#include <stdlib.h>
#include <stdbool>
#include "inc/gamecore.h"

/**
* @brief 동적 할당을 통해 이차원 배열처럼 쓸 수 있는 이중 포인터를 반환한다.
* @param type_size 이중 포인터의 타입
* @param width 이중 포인터의 가로 길이
* @param height 이중 포인터의 세로 길이
* @return 이중 포인터
*/
void** malloc_double_pointer(int type_size, int width, int height)
{
    void** grid = malloc(sizeof(void*) * width);
    if (grid == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < width; i++)
    {
        grid[i] = malloc(type_size * height);
        if (grid[i] == NULL)
        {
            return NULL;
        }
    }
    return grid;
}

/**
* @brief 동적 할당을 통해 생성한 이중 포인터를 할당 해제한다.
* @param width 가로 길이
*/
void free_double_pointer(void** grid, int width)
{
    for (int x = 0; x < width; x++)
    {
        free(grid[x]);
    }
    free(grid);
}

/**
* @brief SG_EMPTY로 초기화한 격자를 생성한다.
* @param width 격자의 가로 길이
* @param width 격자의 세로 길이
* @return 격자 이중 포인터
*/
char** generate_grid(int width, int height)
{
    char** grid = malloc_double_pointer(sizeof(char), width, height);
    if (grid == NULL)
    {
        return NULL;
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            grid[x][y] = SG_EMPTY;
        }
    }
    return grid;
}



bool check_double_three(char** grid, int x, int y)
{
	// 흑의 턴
		/*b=검은돌 w=흰돌 */

			// 가로 
	int countblack = 1; // 두는 곳은 흑색이므로 1 추가
	int countempty = 0;
	int countwhite = 0;
	int 33check = 0;
	int opencheck = 0;

	// 가로 우측 방향 체크
	for (int i = 1; i < 4; i++)
	{
		if (x + i > 18)
			break;

		if (grid[y][x + i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y][x + i] != w)
		{
			if (grid[y][x + i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
		// 4번째 칸이 백돌일 경우 추가 진행
		if (i == 3 && x + i + 1 < 19)
			if (grid[y][x + i + 1] == w)
				countwhite++;
	}

	// 한쪽이 열린 3인지 체킹
	if (countempty > countwhite)
		opencheck = 1;

	// 가로 좌측 방향 체크
	for (int i = 1; i < 4; i++)
	{
		if (x - i < 0)
			break;

		if (grid[y][x - i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y][x - i] != w)
		{
			if (grid[y][x - i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
		// 4번째 칸이 백돌일 경우 추가 진행
		if (i == 3 && x - i - 1 > 0)
			if (grid[y][x - i - 1] == w)
				countwhite++;
	}
	// 열린 3인 경우
	if (countempty - countwhite > 3 && opencheck = 1 && countblack == 3)
		33check += 1;  // 가로 방향 33

		// 세로 
	countblack = 1;
	countempty = 0;
	countwhite = 0;
	opencheck = 0;

	// 세로 아래 방향 체크
	for (int i = 1; i < 4; i++)
	{

		if (y + i > 18)
			break;

		if (grid[y + i][x] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y + i][x] != w)
		{
			if (grid[y + i][x] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
		// 4번째 칸이 백돌일 경우 추가 진행
		if (i == 3 && y + i + 1 < 19)
			if (grid[y + i + 1][x] == w)
				countwhite++;
	}

	// 한쪽이 열린 3인지 체킹
	if (countempty > countwhite)
		opencheck = 1;



	// 세로 위 방향
	for (int i = 1; i < 4; i++)
	{

		if (y - i < 0)
			break;

		if (grid[y - i][x] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y - i][x] != w)
		{
			if (grid[y - i][x] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
		// 4번째 칸이 백돌일 경우 추가 진행
		if (i == 3 && y - i - 1 < 0)
			if (grid[y - i - 1][x] == w)
				countwhite++;
	}

	// 열린 3인 경우
	if (countempty - countwhite > 3 && opencheck = 1 && countblack == 3)
		33check += 1;  // 세로 방향 33 


		// 우측으로 떨어지는 대각선

	countblack = 1;
	countempty = 0;
	countwhite = 0;
	opencheck = 0;

	// 대각선 아래쪽 
	for (int i = 1; i < 4; i++)
	{

		if (y + i > 18 || x + i > 18)
			break;

		if (grid[y + i][x + i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y + i][x + i] != w)
		{
			if (grid[y + i][x + i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}

		// 4번째 칸이 백돌일 경우 추가 진행
		if (i == 3 && y + i + 1 < 19 && x + i + 1 < 19)
			if (grid[y + i + 1][x + i + 1] == w)
				countwhite++;
	}

	// 한쪽이 열린 3인지 체킹
	if (countempty > countwhite)
		opencheck = 1;

	// 대각선 위쪽
	for (int i = 1; i < 4; i++)
	{

		if (y - i < 0 || x - i < 0)
			break;

		if (grid[y - i][x - i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y - i][x - i] != w)
		{
			if (grid[y - i][x - i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}

		// 4번째 칸이 백돌일 경우 추가 진행
		if (i == 3 && y - i - 1 > 0 && x - i - 1 > 0)
			if (grid[y - i - 1][x - i - 1] == w)
				countwhite++;
	}
	// 열린 3인 경우
	if (countempty - countwhite > 3 && opencheck = 1 && countblack == 3)
		33check += 1;  // 우측으로 떨어지는 대각선 33 판정


		// 좌측으로 떨어지는 대각선
	countblack = 1;
	countempty = 0;
	countwhite = 0;
	opencheck = 0;

	// 대각선 아래 방향
	for (int i = 1; i < 4; i++)
	{

		if (y + i > 18 || x - i < 0)
			break;

		if (grid[y + i][x - i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y + i][x - i] != w)
		{
			if (grid[y + i][x - i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}

		// 4번째 칸이 백돌일 경우 추가 진행
		if (i == 3 && y + i + 1 < 19 && x - i - 1 > 0)
			if (grid[y + i + 1][x - i - 1] == w)
				countwhite++;
	}
	// 한쪽이 열린 3인지 체킹
	if (countempty > countwhite)
		opencheck = 1;

	// 대각선 위 방향
	for (int i = 1; i < 4; i++)
	{

		if (y - i < 0 || x + i >18)
			break;

		if (grid[y - i][x + i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y - i][x + i] != w)
		{
			if (grid[y - i][x + i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}

		// 4번째 칸이 백돌일 경우 추가 진행
		if (i == 3 && y - i - 1 > 0 && x + i + 1 < 19)
			if (grid[y - i - 1][x + i + 1] == w)
				countwhite++;
	}
	// 열린 3인 경우
	if (countempty - countwhite > 3 && opencheck = 1 && countblack == 3)
		33check += 1;  // 좌측으로 떨어지는 대각선 33 판정


    // 3*3 판정에서 가로,세로,우측 대각선, 좌측 대각선에서 2개 이상이 판정 될 경우, 3*3으로 취급하여 금수가 됨.
	if (33check >= 2)
	{
		return false;  // 금수 처리
	}

	return true;
}


bool check_double_four(char** grid, int x, int y)
{
	int countblack = 1; // 두는 곳은 흑색이므로 1 추가
	int countempty = 0;
	int countwhite = 0;
	int 44check = 0;
	int opencheck = 0;

	//가로
	for (int i = 1; i < 5; i++) {
		if (x + i > 18)
			break;
		if (grid[y][x + i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y][x + i] != w)
		{
			if (grid[y][x + i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
	}

	for (int i = 1; i < 5; i++)
	{
		if (x - i < 0)
			break;

		if (grid[y][x - i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y][x - i] != w)
		{
			if (grid[y][x - i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
	}

	// 열린 4인 경우
	if (countempty >= countwhite && countblack == 4)
		44check += 1;  // 가로 방향 44 

		// 세로
	countblack = 1;
	countempty = 0;
	countwhite = 0;

	for (int i = 1; i < 5; i++)
	{
		if (y + i > 18)
			break;

		if (grid[y + i][x] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y + i][x] != w)
		{
			if (grid[y + i][x] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
	}

	for (int i = 1; i < 5; i++)
	{
		if (y - i < 0)
			break;

		if (grid[y - i][x] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y - i][x] != w)
		{
			if (grid[y - i][x] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
	}

	// 열린 4인 경우
	if (countempty >= countwhite && countblack == 4)
		44check += 1; // 세로 방향 44 

		// 우측으로 떨어지는 대각선
	countblack = 1;
	countempty = 0;
	countwhite = 0;

	// 대각선 아래

	for (int i = 1; i < 5; i++)
	{
		if (y + i > 18 || x + i > 18)
			break;

		if (grid[y + i][x + i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y + i][x + i] != w)
		{
			if (grid[y + i][x + i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
	}

	// 대각선 위

	for (int i = 1; i < 5; i++)
	{
		if (y - i < 0 || x - i < 0)
			break;

		if (grid[y - i][x - i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y - i][x - i] != w)
		{
			if (grid[y - i][x - i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
	}

	// 열린 4인 경우
	if (countempty >= countwhite && countblack == 4)
		44check = 1;  // 우측으로 떨어지는 대각선 44 

		// 좌측으로 떨어지는 대각선

	countblack = 1;
	countempty = 0;
	countwhite = 0;

	// 대각선 아래

	for (int i = 1; i < 5; i++)
	{
		if (y + i > 18 || x - i < 0)
			break;

		if (grid[y + i][x - i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y + i][x - i] != w)
		{
			if (grid[y + i][x - i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
	}

	// 대각선 위

	for (int i = 1; i < 5; i++)
	{
		if (y - i < 0 || x + i > 18)
			break;

		if (grid[y - i][x + i] == w)
		{
			countwhite++;
			break;
		}
		else if (grid[y - i][x + i] != w)
		{
			if (grid[y - i][x + i] == b)
			{
				countblack++;
			}
			else
			{
				countempty++;
			}
		}
	}

	// 열린 4인 경우
	if (countempty >= countwhite && countblack == 4)
		44check = 1;  // 좌측으로 떨어지는 대각선 방향 44 

	// 4*4 판정에서 가로,세로,우측 대각선, 좌측 대각선에서 2개 이상이 판정 될 경우, 4*4으로 취급하여 금수가 됨.
	else if (44check >= 2)
	{
		return false;  // 금수 처리
	}


	char copygrid[19][19] == {0};
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			copygrid[i][j] = grid[i][j];
			if (copygrid[i][j] != b && coprygrid[i][j] != w)
				copygrid[i][j] == e;
		}
	}

	copygrid[x][y] == b;

	// 추가 경우의 수
	// B B 빈칸 B B 빈칸 B B
	for (int j = 0; j < 12; j++) // 가로
	{
		if (copygrid[j][y] == b && copygrid[j + 1][y] == b && copygrid[j + 2][y] == e && copygrid[j + 3][y] == b && copygrid[j + 4][y] == b && copygrid[j + 5][y] == e && copygrid[j + 6][y] == b && copygrid[j + 7][y] == b)
			return false;
	}

	for (int i = 0; i < 12; i++) // 세로
	{
		if (copygrid[x][i] == b && copygrid[x][i + 1] == b && copygrid[x][i + 2] == e && copygrid[x][i + 3] == b && copygrid[x][i + 4] == b && copygrid[x][i + 5] == e && copygrid[x][i + 6] == b && copygrid[x][i + 7] == b)
			return false;
	}

	for (int j = 0; j < 12; j++) // 우측으로 떨어지는 대각선
	{
		for (int i = 0; i < 12; i++)
		{
			if (copygrid[j][i] == b && copygrid[j + 1][i + 1] == b && copygrid[j + 2][i + 2] == e && copygrid[j + 3][i + 3] == b && copygrid[j + 4][i + 4] == b && copygrid[j + 5][i + 5] == e && copygrid[j + 6][i + 6] == b && copygrid[j + 7][i + 7] == b)
				return false;
		}
	}
	for (int j = 7; j < 19; j++) // 좌측으로 떨어지는 대각선
	{
		for (int i = 0; i < 12; i++)
		{
			if (copygrid[j][i + 7] == b && copygrid[j - 1][i + 6] == b && copygrid[j - 2][i + 5] == e && copygrid[j - 3][i + 4] == b && copygrid[j - 4][i + 3] == b && copygrid[j - 5][i + 2] == e && copygrid[j - 6][i + 1] == b && copygrid[j - 7][i] == b)
				return false;
		}
	}

	// B 빈칸 B B B 빈칸 B

	for (int j = 0; j < 13; j++) // 가로
	{
		if (copygrid[j][y] == b && copygrid[j + 1][y] == e && copygrid[j + 2][y] == b && copygrid[j + 3][y] == b && copygrid[j + 4][y] == b && copygrid[j + 5][y] == e && copygrid[j + 6][y] == b)
			return false;
	}


	for (int i = 0; i < 13; i++) // 세로
	{
		if (copygrid[x][i] == b && copygrid[x][i + 1] == e && copygrid[x][i + 2] == b && copygrid[x][i + 3] == b && copygrid[x][i + 4] == b && copygrid[x][i + 5] == e && copygrid[x][i + 6] == b)
			return false;
	}

	for (int j = 0; j < 13; j++) // 우측으로 떨어지는 대각선
	{
		for (int i = 0; i < 13; i++)
		{
			if (copygrid[j][i] == b && copygrid[j + 1][i + 1] == e && copygrid[j + 2][i + 2] == b && copygrid[j + 3][i + 3] == b && copygrid[j + 4][i + 4] == b && copygrid[j + 5][i + 5] == e && copygrid[j + 6][i + 6] == b)
				return false;
		}
	}
	for (int j = 6; j < 19; j++) // 좌측으로 떨어지는 대각선
	{
		for (int i = 0; i < 13; i++)
		{
			if (copygrid[j][i + 6] == b && copygrid[j - 1][i + 5] == e && copygrid[j - 2][i + 4] == b && copygrid[j - 3][i + 3] == b && copygrid[j - 4][i + 2] == b && copygrid[j - 5][i + 1] == e && copygrid[j - 6][i] == b)
				return false;
		}
	}

	return true;
}

bool check_overline(char** grid, int x, int y)
{
	char copygrid[19][19] == {0};
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
			copygrid[i][j] = grid[i][j];
	}

	for (int j = 0; j < 13; j++) // 가로
	{
		if (copygrid[j][y] == b && copygrid[j + 1][y] == b && copygrid[j + 2][y] == b && copygrid[j + 3][y] == b && copygrid[j + 4][y] == b && copygrid[j + 5][y] == b)
			return false;
	}


	for (int i = 0; i < 13; i++) // 세로
	{
		if (copygrid[x][i] == b && copygrid[x][i + 1] == b && copygrid[x][i + 2] == b && copygrid[x][i + 3] == b && copygrid[x][i + 4] == b && copygrid[x][i + 5] == b)
			return false;
	}

	for (int j = 0; j < 14; j++) // 우측으로 떨어지는 대각선
	{
		for (int i = 0; i < 14; i++)
		{
			if (copygrid[j][i] == b && copygrid[j + 1][i + 1] == b && copygrid[j + 2][i + 2] == b && copygrid[j + 3][i + 3] == b && copygrid[j + 4][i + 4] == b && copygrid[j + 5][i + 5] == b)
				return false;
		}
	}
	for (int j = 5; j < 19; j++) // 좌측으로 떨어지는 대각선
	{
		for (int i = 0; i < 14; i++)
		{
			if (copygrid[j][i + 5] == b && copygrid[j - 1][i + 4] == b && copygrid[j - 2][i + 3] == b && copygrid[j - 3][i + 2] == b && copygrid[j - 4][i + 1] == b && copygrid[j - 5][i] == b)
				return false;
		}
	}

	return true;
}

bool check_confirm()
{
	if (check_double_three == true && check_double_four == true && check_overline == true)
		return true;
	else
		return false;
}