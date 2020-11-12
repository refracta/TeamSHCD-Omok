#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <Windows.h>
#include "inc/systemutils.h"
#include "inc/consoleutils.h"

/**
 * @brief 콘솔 커서의 가시 상태를 변경한다.
 * @param visibility 가시 상태
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
 * @brief 콘솔의 출력 위치를 설정한다.
 * @param x 가로줄 출력 위치
 * @param y 세로줄 출력 위치
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
 * @brief 출력 텍스트의 색깔을 설정한다.
 * @param text_color 텍스트의 색깔
 * @param background_color 텍스트의 배경 색깔
 */
void set_print_color(int text_color, int background_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color + background_color * 16);
}

/**
 * @brief 화면을 초기화한다.
 */
void clear_console()
{
	system("cls");
}

/**
 * @brief 사용자가 누른 키를 가져온다.
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
 * @brief wait 중 키 핸들링을 같이 수행한다.
 * @description wait를 UNIT_WAIT로 쪼개어 수행하고 도중 키가 눌렸는지 검사하여 handler에 전달한다.
 *	handler(int c)의 반환값이 1 이상일 때 wait를 중지하고 handler의 반환 값을 반환한다.
 *	키 핸들링이 일어나지 않는 경우에는 항상 -1을 반환한다.
 * @param ms 대기할 시간 (밀리초)
 * @param handler 텍스트의 배경 색깔
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
 * @brief 콘솔의 x, y 위치에 printf 함수와 같은 기능을 수행한다.
 * @param x 가로줄 출력 위치
 * @param y 세로줄 출력 위치
 * @param format 포맷 문자열
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