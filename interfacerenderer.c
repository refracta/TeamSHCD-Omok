/**
  @file interfacerenderer.c
  @brief 인터페이스 렌더러
*/
#include "inc/environment.h"
#include "inc/consoleutils.h"
#include "inc/interfacerenderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdbool.h>
#include <math.h>

/**
* @brief 문자열이 전각인지 검사한다.
* @param s wchar_t 문자열
* @return 전각 여부 bool
*/
bool is_full_width(wchar_t c) 
{
	if (c < 256 || (c >= 0xff61 && c <= 0xff9f)) {
		return false;
	}
	else
	{
		return true;
	}
}

/**
* @brief 전각은 2글자로, 반각은 1글자로 계산한 문자의 길이를 계산한다.
* @param s wchar_t 문자열
* @return 문자열의 길이 
*/
int strrlen(wchar_t * s) 
{
	int len = wcslen(s);
	int rlen = len;
	for (int i = 0; i < len; i++) 
	{
		rlen += is_full_width(s[i]);
	}
	return rlen;
}

/**
* @brief 지정한 틱의 인트로 애니메이션 장면을 그린다.
* @param tick 인트로 애니메이션 틱
*/
void draw_intro(int tick) 
{
	if (tick == 0) 
	{
		clear_console();
		set_cursor_position(0, 0);
	}

	COORD position = get_cursor_position();
	short color = get_print_color();

	set_print_color(TO_TBCOLOR(WHITE, BLACK));
	int title_x = 36;
	xyprintf(title_x, 1, "%s", ASCII_TITLE_SHCD);
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
		xyprintf(1, 19, u8"Java 두명 타세요 ...");

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
void draw_menu(MenuData* data) 
{
	short color = get_print_color();

	int max_length = strrlen(data->name);
	for (int i = 0; i < data->length; i++) 
	{
		max_length = MAX(max_length, strrlen(data->list[i]));
	}
	set_print_color(data->outline_tbcolor);
	xywprintf(data->x, data->y, L"┌──");
	set_print_color(data->name_tbcolor);
	wprintf(L"[ %s%*s ]", data->name, (int)(max_length - strrlen(data->name)), L"");
	set_print_color(data->outline_tbcolor);
	wprintf(L"─┐ ");

	for (int i = 0; i < data->length; i++) 
	{
		set_print_color(data->outline_tbcolor);
		xywprintf(data->x, data->y + (i + 1), L"│ ");
		if (i != data->current_index) 
		{
			set_print_color(data->non_selected_tbcolor);
		}
		else
		{
			set_print_color(data->selected_tbcolor);
		}
		wprintf(L"   %s%*s   ", data->list[i], (int)(max_length - strrlen(data->list[i])), L"");
		set_print_color(data->outline_tbcolor);
		wprintf(L"│ ");
	}

	xywprintf(data->x, data->y + data->length + 1, L"└────");
	for (int i = 0; i < max_length; i++) 
	{
		wprintf(L"─");
	}
	wprintf(L"───┘ ");
	set_print_color(color);
}

/**
* @brief 프롬프트를 그린다.
* @param data 프롬프트 정보 데이터
*/
void draw_prompt(PromptData* data) {
	short color = get_print_color();
	int max_length = MAX(data->rlen, strrlen(data->message));

	set_print_color(data->outline_tbcolor);
	xywprintf(data->x, data->y, L"┌──");
	set_print_color(data->message_tbcolor);
	wprintf(L"[ %s%*s ]", data->message, (int)(max_length - strrlen(data->message)), L"");
	set_print_color(data->outline_tbcolor);
	wprintf(L"─┐ ");
	set_print_color(data->outline_tbcolor);
	xywprintf(data->x, data->y + 1, L"│   %*s    │ ", max_length, L"");
	xywprintf(data->x, data->y + 2, L"└────");
	for (int i = 0; i < max_length; i++)
	{
		wprintf(L"─");
	}
	wprintf(L"───┘ ");
	set_print_color(color);
}

/**
* @brief 타이머를 그린다.
* @param data 타이머 정보 데이터
*/
void draw_timer(TimerData* data)
{
	short original_color = get_print_color();
	
	/* outline */
	set_print_color(data->outline_tbcolor);
	xywprintf(data->x, data->y, L"%s", L"┌");
	for (int i = 0; i < ((data->width) - 2); i++)
		wprintf(L" %s", L"─");

	wprintf(L" %s", L"┐ ");
	xywprintf(data->x, (data->y) + 1, L"%s", L"│ ");
	xywprintf(data->x + data->width * 2 - 2, (data->y) + 1, L"%s", L"│ ");

	xywprintf(data->x, (data->y) + 2, L"%s", L"└");
	for (int i = 0; i < ((data->width) - 2); i++)
		wprintf(L" %s", L"─");
	wprintf(L" %s", L"┘ ");

	xywprintf(data->x + data->width * 2 - 6, data->y + 1, L"%s", L"│ ");
	xywprintf(data->x + data->width * 2 - 4, data->y + 1, L"%02d", data->left_seconds);

	/* bar */
	set_print_color(TO_TBCOLOR(TO_BACKGROUND_COLOR(data->bar_tbcolor), TO_TEXT_COLOR(data->bar_tbcolor)));
    set_cursor_position(data->x + 2, data->y + 1);
    for (int i = 0; i < (data->width - 4); i++)
        wprintf(L"%s", L"　");

    set_print_color(data->bar_tbcolor);
    set_cursor_position(data->x + 2, data->y + 1);
    for (int i = 0; i < (int)(((data->width - 4) * (double)data->percent / 100.0)); i++)
		wprintf(L"%s", L"　");
	set_print_color(original_color);
}