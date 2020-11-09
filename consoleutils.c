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
	cursorInfo.bVisible = visibility;
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
	while (kbhit()) 
	{
		return getchar();
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