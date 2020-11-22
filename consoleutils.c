/**
  @file consoleutils.c
  @brief 콘솔 유틸
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>
#include "inc/systemutils.h"
#include "inc/consoleutils.h"

/**
 * @brief wchar_t 계열 문자열 처리를 위해 지역 설정을 ko-KR로 변경합니다.
 */
void set_locale_korean() {
	setlocale(LC_ALL, "ko-KR");
}

/**
 * @brief wchar_t 계열 문자열 처리를 위해 지역 설정을 기본 값으로 변경합니다.
 */
void set_locale_default() {
	setlocale(LC_ALL, "C");
}

/**
 * @brief 현재 콘솔 인코딩 설정을 CP949로 변경합니다.
 */
void set_encoding_cp949() {
	system("chcp 949 > NUL");
}

/**
 * @brief UTF8 프로젝트의 한글 출력을 위해 콘솔 인코딩을 변경합니다.
 */
void set_encoding_utf8() {
	system("chcp 65001 > NUL");
}

/**
 * @brief ASCII Animation을 위한 빠른 출력 모드로 설정합니다.
 */
void set_boost_mode() {
	set_locale_default();
	set_encoding_utf8();
}

/**
 * @brief 출력 속도는 상대적으로 느리지만 콘솔 한글 입출력 가용성이 최대한 보장되는 기본 모드로 설정합니다.
 */
void set_default_mode() {
	set_locale_korean();
	set_encoding_cp949();
}

/**
 * @brief 콘솔 커서의 가시 상태를 반환한다.
 * @return 가시 상태 부울
 */
bool get_cursor_visibility()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursor_info;

	GetConsoleCursorInfo(out, &cursor_info);
	return cursor_info.bVisible;
}

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

/**
 * @brief 콘솔 커서의 크기를 설정한다.
 * @param cursor_size 커서 크기 (0~100)
 */
void set_cursor_size(int cursor_size) {
	CONSOLE_CURSOR_INFO cursor_info;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(handle, &cursor_info);
	cursor_info.dwSize = cursor_size;
	SetConsoleCursorInfo(handle, &cursor_info);
}

/**
 * @brief 콘솔의 출력 위치를 가져온다.
 * @return 출력 위치 구조체
 */
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
 * @param tbcolor 텍스트의 색깔 + 텍스트의 배경 색깔 * 16
 * @param background_color 텍스트의 배경 색깔
 */
void set_print_color(int tbcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), tbcolor);
}


/**
 * @brief 출력 텍스트의 색깔값을 가져온다
 * @return 출력 텍스트의 색깔값 (텍스트의 색깔 + 텍스트의 배경 색깔 * 16)
 */
short get_print_color() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.wAttributes;
}

/**
 * @brief 화면의 크기를 설정한다.
 * @cols 텍스트 열의 수
 * @lines 텍스트 행의 수
 */
void set_console_size(int cols, int lines) {
	char cmd[BUFSIZ];
	sprintf(cmd, "mode con: cols=%d lines=%d", cols, lines);
	system(cmd);
}

/**
 * @brief 창 제목을 설정한다.
 * @title 창 제목
 */
void set_console_title(const char* title) {
	SetConsoleTitle(title);
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
 * @return _getwch() value
 */
int get_key_input() {
	while (true)
	{

		if (_kbhit())
		{
            int c = _getwch();
            c = (c == 0xE0 || c == 0) ? _getwch() : c;
            return c;
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
 * @param data 자유형 데이터
 */
int wait_with_handler(unsigned long ms, int (*handler)(int, void*), void* data)
{
	struct timespec begin, end;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	while (true)
	{
		wait(UNIT_WAIT);
        if (_kbhit())
        {
            int c = _getwch();
            c = (c == 0xE0 || c == 0) ? _getwch() : c;
			int result = handler(c, data);
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
void xyprintf(int x, int y, char* format, ...)
{
	char buffer[BUFSIZ];
	int buffer_size = sizeof(buffer) / sizeof(char);
	char* buffer_ptr = buffer;

	va_list arg_ptr;
	va_start(arg_ptr, format);
	int length = vsnprintf(buffer_ptr, buffer_size, format, arg_ptr) + 1;
	va_end(arg_ptr);

	if (length > buffer_size)
	{
		buffer_ptr = malloc(sizeof(char) * length);
		if (buffer_ptr == NULL) {
			return;
		}
		buffer_size = length;

		va_start(arg_ptr, format);
		length = vsnprintf(buffer_ptr, buffer_size, format, arg_ptr) + 1;
		va_end(arg_ptr);
	}

	COORD position = get_cursor_position();
	x = x < 0 ? position.X : x;
	y = y < 0 ? position.Y : y;

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

	if (buffer_ptr != buffer)
	{
		free(buffer_ptr);
	}
}

/**
 * @brief 콘솔의 x, y 위치에 wprintf 함수와 같은 기능을 수행한다.
 * @param x 가로줄 출력 위치
 * @param y 세로줄 출력 위치
 * @param format 포맷 문자열
 */
void xywprintf(int x, int y, wchar_t* format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	int buffer_size = _vscwprintf(format, arg_ptr) + 1;
	va_end(arg_ptr);

	wchar_t* buffer_ptr = malloc(sizeof(wchar_t) * buffer_size);
	if (buffer_ptr == NULL) {
		return;
	}
	va_start(arg_ptr, format);
	_vsnwprintf(buffer_ptr, buffer_size, format, arg_ptr);
	va_end(arg_ptr);

	COORD position = get_cursor_position();
	x = x < 0 ? position.X : x;
	y = y < 0 ? position.Y : y;

	int delta = 0;
	wchar_t* target = buffer_ptr;
	for (int i = 0; i < buffer_size; i++)
	{
		if (buffer_ptr[i] == '\n' || buffer_ptr[i] == '\0')
		{
			buffer_ptr[i] = '\0';
			set_cursor_position(x, y + delta++);
			wprintf(L"%s", target);
			target = buffer_ptr + i + 1;
		}
	}
	free(buffer_ptr);
}