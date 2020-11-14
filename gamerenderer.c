#include <stdio.h>
#include "inc/gamerenderer.h"

void render_grid(char** grid, int width, int height);
void play_put_stone_animation(char grid[][13], int stone_x, int stone_y);

/**
* @brief ���� �ִ� �迭�� �Է¹޾Ƽ� ���ڿ� �Բ� ������ִ� �Լ�
* @param grid �� ��ġ�� ��� �迭(13x13 ����, �浹�� 'b', �鵹�� 'w')
* @param width ������ ���� ũ��
* @param height ������ ���� ũ��
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
				printf("%s", RG_GRID_TYPE_7);//�»�� ����
			else if (i == first_index && j == last_w_index)
				printf("%s", RG_GRID_TYPE_9);//���� ����
			else if (i == first_index)
				printf("%s", RG_GRID_TYPE_8);//��� ����
			else if (i != last_h_index && j == first_index)
				printf("%s", RG_GRID_TYPE_4);//���� ����
			else if (i != last_h_index && j == last_w_index)
				printf("%s", RG_GRID_TYPE_6);//���� ����
			else if (i == last_h_index && j == first_index)
				printf("%s", RG_GRID_TYPE_1);//���ϴ� ����
			else if (i == last_h_index && j == last_w_index)
				printf("%s", RG_GRID_TYPE_3);//���ϴ� ����
			else if (i == last_h_index)
				printf("%s", RG_GRID_TYPE_2);//�ϴ� ����
			else
				printf("%s", RG_GRID_TYPE_5); //�𼭸��� �ƴ� ����
			if (j != last_w_index) 
				printf("%s", RG_GRID_TYPE_H); //���ڰ� ���Ʒ��� ������� ���ι��� �ϳ��� �־� ���簢������ ���̰� ��
		}
		printf("\n");
	}

	//�� ����
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j] == 'b')
				xyprint(j * 2, i, RG_BLACK); //����� ���� ���־ ���� ���� Ƣ����� �κ��� �ذ� ���ص� ��.
			else if (grid[i][j] == 'w')
			{
				if ((grid[i][j - 1] == 'w' || grid[i][j - 1] == 'b') || j == 0) //��(����ִ� ���׶��)���� 1. �ٷ� �տ� ���� �����ְų� 2. ù ���� ���� ��쿣 ���ڹ��� ó�� ����
					xyprint(j * 2, i, RG_WHITE);
				else
					xyprint(j * 2 - 1, i, " " RG_WHITE); //������ ��쿣, �� ĭ �տ������� [���� + ��]�� �׸���.
			}
		}
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