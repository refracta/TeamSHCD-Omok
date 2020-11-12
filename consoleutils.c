#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <Windows.h>
#include "inc/systemutils.h"
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
	cursor_info.bVisible = visibility;
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

COORD get_cursor_position()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
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
	while (true) 
	{
		if (kbhit()) 
		{
			return getch();
		}
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
			int result = handler(getch());
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


/**
 * @brief �ܼ��� x, y ��ġ�� printf �Լ��� ���� ����� �����Ѵ�.
 * @param x ������ ��� ��ġ
 * @param y ������ ��� ��ġ
 * @param format ���� ���ڿ�
 */
void xyprint(int x, int y, char* format, ...)
{
	char buffer[BUFSIZ];
	int buffer_size = sizeof(buffer);
	char* buffer_ptr = buffer;

	va_list arg_ptr;
	va_start(arg_ptr, format);
	int length = vsnprintf(buffer_ptr, buffer_size, format, arg_ptr) + 1;
	va_end(arg_ptr);

	if (length > sizeof(buffer))
	{
		buffer_ptr = malloc(length);
		if (buffer_ptr == NULL) {
			return;
		}
		buffer_size = length;

		va_start(arg_ptr, format);
		length = vsnprintf(buffer_ptr, buffer_size, format, arg_ptr) + 1;
		va_end(arg_ptr);
	}

	COORD position = get_cursor_position();
	int delta = 0;
	char* target = buffer_ptr;
	for (int i = 0; i < length; i++)
	{
		if (buffer_ptr[i] == '\n' || buffer_ptr[i] == '\0')
		{
			buffer_ptr[i] = '\0';
			set_cursor_position(x, y + delta++);
			printf("%s", target);
			target = buffer_ptr + i + 1;
		}
	}
	set_cursor_position(position.X, position.Y);

	if (buffer_ptr != buffer)
	{
		free(buffer_ptr);
	}
}