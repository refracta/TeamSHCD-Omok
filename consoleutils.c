#include "inc/consoleutils.h"

/**
 * @brief �ܼ� Ŀ���� ���� ���¸� �����Ѵ�.
 * @param visibility ���� ����
 */
void set_cursor_visibility(bool visibility)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursor_info;

	GetConsoleCursorInfo(out, &cursor_info);
	cursorInfo.bVisible = visibility;
	SetConsoleCursorInfo(out, &cursor_info);
}

/**
 * @brief �ܼ��� ��� ��ġ�� �����Ѵ�.
 * @param x ������ ��� ��ġ
 * @param y ������ ��� ��ġ
 */
void set_cursor_position(int x, int y) 
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

/**
 * @brief ��� �ؽ�Ʈ�� ������ �����Ѵ�.
 * @param text_color �ؽ�Ʈ�� ����
 * @param background_color �ؽ�Ʈ�� ��� ����
 */
void set_print_color(int text_color, int background_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color + background_color * 16);
}

/**
 * @brief ȭ���� �ʱ�ȭ�Ѵ�.
 */
void clear_console() 
{
	system("cls");
}

/**
 * @brief ����ڰ� ���� Ű�� �����´�.
 * @return getchar() value
 */
int get_key_input() {
	while (kbhit()) 
	{
		return getchar();
	}
}

/**
 * @brief wait �� Ű �ڵ鸵�� ���� �����Ѵ�.
 * @description wait�� UNIT_WAIT�� �ɰ��� �����ϰ� ���� Ű�� ���ȴ��� �˻��Ͽ� handler�� �����Ѵ�. 
 *	handler(int c)�� ��ȯ���� 1 �̻��� �� wait�� �����ϰ� handler�� ��ȯ ���� ��ȯ�Ѵ�. 
 *	Ű �ڵ鸵�� �Ͼ�� �ʴ� ��쿡�� �׻� -1�� ��ȯ�Ѵ�.
 * @param ms ����� �ð� (�и���)
 * @param handler �ؽ�Ʈ�� ��� ����
 */
int wait_with_handler(unsigned long ms, int (*handler)(int))
{
	struct timespec begin, end;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	while (true)
	{
		wait(UNIT_WAIT);
		if (kbhit()) 
		{
			int result = handler(getchar());
			if (result > -1) 
			{
				return result;
			}
		}
		clock_gettime(CLOCK_MONOTONIC, &end);
		if (MILLISECOND_DIFF(begin, end) >= ms) 
		{
			return -1;
		}
	}
}