#include <stdlib.h>
#include "inc/gamecore.h"

/**
* @brief ���� �Ҵ��� ���� ������ �迭ó�� �� �� �ִ� ���� ���� �����͸� ��ȯ�Ѵ�.
* @param width ������ ���� ����
* @param height ������ ���� ����
* @return ���� ���� ������
*/
char** malloc_grid(int width, int height) 
{
	char** grid = malloc(sizeof(char*) * width);
    if (grid == NULL) 
    {
        return NULL;
    }
    for (int i = 0; i < width; i++)
    {
        grid[i] = malloc(sizeof(char) * height);
        if (grid[i] == NULL) 
        {
            return NULL;
        }
    }
    return grid;
}

/**
* @brief ���� �Ҵ��� ���� ������ ���� ���� �����͸� �Ҵ� �����Ѵ�.
* @param width ������ ���� ����
*/
void free_grid(char ** grid, int width)
{
    for (int x = 0; x < width; x++)
    {
        free(grid[x]);
    }
    free(grid);
}

/**
* @brief SG_EMPTY�� �ʱ�ȭ�� ���ڸ� �����Ѵ�.
* @param width ������ ���� ����
* @param width ������ ���� ����
* @return ���� ���� ������
*/
char** generate_grid(int width, int height)
{
    char** grid = malloc_grid(width, height);
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