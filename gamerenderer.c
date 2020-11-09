#include <stdio.h>

void render_grid(char[][13]);
void play_put_stone_animation(char grid[][13], int stone_x, int stone_y);

/**
* @brief ���� �ִ� �迭�� �Է¹޾Ƽ� ���ڿ� �Բ� ������ִ� �Լ�
* @param grid[][13] �� ��ġ�� ��� �迭(13x13 ����, �浹�� 'b', �鵹�� 'w')
* @return ����.
*/
void render_grid(char grid[][13])
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (grid[i][j] == 'b')
				printf("��"); //�𼭸��� �ƴ� ����
			else if (grid[i][j] == 'w')
				printf("��"); //�𼭸��� �ƴ� ����
			else
			{
				if (i == 0 && j == 0) //�»�� ����
					printf("��");
				else if (i == 0 && j == 12) //���� ����
					printf("��");
				else if (i == 0) //��� ����
					printf("��");
				else if (i != 12 && j == 0) //���� ����
					printf("��");
				else if (i != 12 && j == 12) //���� ����
					printf("��");
				else if (i == 12 && j == 0) //���ϴ� ����
					printf("��");
				else if (i == 12 && j == 12) //���ϴ� ����
					printf("��");
				else if (i == 12) //�ϴ� ����
					printf("��");
				else
				{
					printf("��"); //�𼭸��� �ƴ� ����
				}
			}
			if (grid[i][j] != 'b' && grid[i][j] != 'w' && j != 12) //���ڰ� ���Ʒ��� ������� ���ι��� �ϳ��� �־� ���簢������ ���̰� ��.
			{
				printf("��");
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