#include "inc/environment.h"
#include "inc/consoleutils.h"
#include "inc/interfacerenderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdbool.h>

bool isFullWidth(wchar_t c) {
	if (c < 256 || (c >= 0xff61 && c <= 0xff9f)) {
		return false;
	}
	else
	{
		return true;
	}
}

int strrlen(wchar_t * s) {
	int len = wcslen(s);
	int rlen = len;
	for (int i = 0; i < len; i++) {
		rlen += isFullWidth(s[i]);
	}
	return rlen;
}

/**
* @brief 지정한 틱의 인트로 애니메이션 장면을 그린다.
* @param tick 인트로 애니메이션 틱
*/
void draw_intro(int tick) {
	if (tick == 0) {
		clear_console();
		set_cursor_position(0, 0);
	}

	COORD position = get_cursor_position();
	short color = get_print_color();

	set_print_color(TO_TBCOLOR(WHITE, BLACK));
	int title_x = 36;
	xyprintf(title_x, 1, "%s", ASCII_TITLE_SCHD);
	xyprintf(title_x, 9, "-----------SeungHapCha Developers----------");

	set_print_color(TO_TBCOLOR(GREEN, BLACK));
	xyprintf(14, 21, "%s", ASCII_PEOPLE1);

	set_print_color(TO_TBCOLOR(PURPLE, BLACK));
	xyprintf(24, 24, "%s", ASCII_DRUM_CAN);

	set_print_color(TO_TBCOLOR(JADE, BLACK));
	xyprintf(34, 19, "%s", ASCII_PEOPLE2);

	set_print_color(TO_TBCOLOR(RED, BLACK));
	if (tick % 12 == 0)
	{
		xyprintf(24, 21, "%s", ASCII_SMOKE2);
	}
	else if (tick % 6 == 0)
	{
		xyprintf(24, 21, "%s", ASCII_SMOKE1);
	}

	set_print_color(TO_TBCOLOR(BLUE, BLACK));
	int car_start_x = 72;
	if (car_start_x - tick >= 20)
	{
		xyprintf(72 - tick, 10, "%s", ASCII_SHC);
		set_cursor_position(position.X, position.Y);
	}
	else
	{
		xyprintf(20, 10, "%s", ASCII_SHC);
		xyprintf(1, 19, "Java 두명 타세요 ...");

		if (tick > 60 + 30)
		{
			set_print_color(TO_TBCOLOR(GREEN, BLACK));
			xyprintf(5, 23, "......");
		}
		if (tick > 60 + 30 + 30)
		{
			set_print_color(TO_TBCOLOR(JADE, BLACK));
			xyprintf(45, 23, "......");
		}
		set_cursor_position(position.X, position.Y);
		if (tick > 70 + 30 + 30 + 30)
		{
			if (position.Y <= 30 - 1 - 1) {
				set_print_color(TO_TBCOLOR(GRAY, BLACK));
				for (int i = 0; i < 120; i++)
				{
					printf(".");
				}
			}
		}
	}
	set_print_color(color);
}

/**
* @brief 메뉴를 그린다.
* @param data 메뉴 정보 데이터
*/
void draw_menu(MenuData* data) {
	short color = get_print_color();

	int max_length = strrlen(data->name);
	for (int i = 0; i < data->length; i++) {
		max_length = MAX(max_length, strrlen(data->list[i]));
	}
	set_print_color(data->outline_tbcolor);
	xywprintf(data->x, data->y, L"┌─");
	set_print_color(data->name_tbcolor);
	wprintf(L"[ %s%*s ]", data->name, (int)(max_length - strrlen(data->name)), L"");
	set_print_color(data->outline_tbcolor);
	wprintf(L"─┐ ");

	for (int i = 0; i < data->length; i++) {
		set_print_color(data->outline_tbcolor);
		xywprintf(data->x, data->y + (i + 1), L"│");
		if (i != data->current_index) {
			set_print_color(data->name_tbcolor);
		}
		else
		{
			set_print_color(data->selected_tbcolor);
		}
		wprintf(L"   %s%*s   ", data->list[i], (int)(max_length - strrlen(data->list[i])), L"");
		set_print_color(data->outline_tbcolor);
		wprintf(L"│ ");
	}

	xywprintf(data->x, data->y + data->length + 1, L"└───");
	for (int i = 0; i < max_length; i++) {
		wprintf(L"─");
	}
	wprintf(L"───┘ ");
	set_print_color(color);
}