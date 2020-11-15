#include <Windows.h>
#include <wchar.h>

#ifndef __CONSOLEUTILS_H__
#define __CONSOLEUTILS_H__
/**
 * @brief 콘솔에서 사용하는 색깔 열거형
 */
typedef enum
{
	BLACK, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE
} ConsoleColor;
#endif

#define TO_TEXT_COLOR(tbcolor) (tbcolor / 16) 
#define TO_BACKGROUND_COLOR(tbcolor) (tbcolor % 16) 
#define TO_TBCOLOR(text_color, background_color) (16 * background_color + text_color)

void set_locale_korean();
void set_locale_default();
void set_encoding_utf8();
void set_cursor_visibility(bool);
void set_cursor_position(int, int);
void set_print_color(int);
short get_print_color();
void set_console_size(int, int);
void set_console_title(const char*);
COORD get_cursor_position();
void clear_console();
int get_key_input();
int wait_with_handler(unsigned long, int (*)(int));
void xyprintf(int, int, char*, ...);
void xywprintf(int, int, wchar_t*, ...);
