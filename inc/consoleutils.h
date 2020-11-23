#ifndef CONSOLEUTILS_H
#define CONSOLEUTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <wchar.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>
#include "systemutils.h"

#define CURSOR_SIZE_SMALL 25
#define CURSOR_SIZE_LARGE 100

#define TO_TEXT_COLOR(tbcolor) (tbcolor % 16)
#define TO_BACKGROUND_COLOR(tbcolor) (tbcolor / 16)
#define TO_TBCOLOR(text_color, background_color) (16 * background_color + text_color)

/**
 * @brief 콘솔에서 사용하는 색깔 열거형
 */
typedef enum
{
    BLACK, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
    LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE
} ConsoleColor;

void set_locale_korean();

void set_locale_default();

void set_encoding_cp949();

void set_encoding_utf8();

void set_boost_mode();

void set_default_mode();

short get_print_color();

void set_print_color();

COORD get_cursor_position();

void set_cursor_position(int x, int y);

bool get_cursor_visibility();

void set_cursor_visibility(bool visibility);

void set_console_size(int cols, int lines);

void set_cursor_size(int cursor_size);

void set_console_title(const char *title);

void clear_console();

void xyprintf(int x, int y, char *format, ...);

void xywprintf(int x, int y, wchar_t *format, ...);

int get_key_input();

int wait_with_handler(unsigned long ms, int (*handler)(int, void *), void *data);

#endif