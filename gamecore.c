/**
  @file gamecore.c
  @brief 게임 코어
*/
#include <stdlib.h>
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