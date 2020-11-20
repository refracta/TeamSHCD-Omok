/**
  @file gameutils.c
  @brief 게임 유틸
*/
#include <stdbool.h>
#include <locale.h>
#include "inc/consoleutils.h"
#include "inc/systemutils.h"
#include "inc/interfacerenderer.h"
#include "inc/keycode.h"

/**
* @brief 메뉴를 실행한다.
* @param data 메뉴 데이터
* @param disable_escape ESC 메뉴 종료 비활성화 여부
* @return 메뉴 항목 색인
*/
int run_menu(MenuData* data, bool disable_escape) {
	int return_value = -1;
	draw_menu(data);
	while (true)
	{
		int c = get_key_input();
		if (c == 0xE0 || c == 0) 
		{
			c = get_key_input();
		}
		switch (c) {
		case ESCAPE_KEY:
			if (!disable_escape)
			{
				return -1;
			}
			break;
		case DOWN_KEY:
			if (data->current_index < data->length - 1) 
			{
				data->current_index++;
				draw_menu(data);
				Beep(349 * 2, 100);
			}
			break;
		case UP_KEY:
			if (data->current_index > 0) 
			{
				data->current_index--;
				draw_menu(data);
				Beep(349 * 2, 100);
			}
			break;
		case SPACE_KEY:
		case ENTER_KEY:
			Beep(494 * 2, 100);
			Beep(392 * 2, 100);
			return data->current_index;
			break;
		}
	}
}

void select_stone_position() 
{
	while (true)
	{
		int c = get_key_input();
		if (c == 0xE0 || c == 0) 
		{
			c = get_key_input();
		}
		switch (c) {
		case ESCAPE_KEY:

			break;
		case UP_KEY:

			break;
		case DOWN_KEY:

			break;
		case RIGHT_KEY:

			break;
		case LEFT_KEY:

			break;
		case SPACE_KEY:
		case ENTER_KEY:

			break;

/**
* @brief 프롬프트를 실행한다.
* @param data 프롬프트 데이터
* @return 프롬프트 입력 텍스트
*/
wchar_t* run_prompt(PromptData* data) {
	bool visibility = get_cursor_visibility();
	short color = get_print_color();
	set_cursor_visibility(true);

	draw_prompt(data);
	set_print_color(data->text_tbcolor);
	set_cursor_position(data->x + 4, data->y + 1);

	int index = 0;
	int crlen = 0;
	wchar_t* text = malloc(sizeof(wchar_t) * data->rlen);
	if (text == NULL) {
		return NULL;
	}
	
	while (true) {
		if (_kbhit()) {
			int c = _getwch();
			if (c == 0xE0 || c == 0) {
				c = _getwch();
			}
			int crl;
			switch (c) {
				default:
					crl = is_full_width(c) ? 2 : 1;
					if (crlen + crl > data->rlen) {
						continue;
					}
					text[index++] = c;
					crlen += crl;
					wprintf(L"%c", c);
					break;
				case BACKSPACE_KEY:
					if (index <= 0) {
						continue;
					}
					set_print_color(data->outline_tbcolor);
					if (is_full_width(text[index - 1])) {
						crlen -= 2;
						wprintf(L"%c%c", BACKSPACE_KEY, BACKSPACE_KEY);
						wprintf(L"  ");
						wprintf(L"%c%c", BACKSPACE_KEY, BACKSPACE_KEY);
					}
					else 
					{
						crlen--;
						wprintf(L"%c", BACKSPACE_KEY);
						wprintf(L" ");
						wprintf(L"%c", BACKSPACE_KEY);
					}
					set_print_color(data->text_tbcolor);
					index--;
					break;
				case ENTER_KEY:
					if (index <= 0) 
					{
						continue;
					}
					text[index] = '\0';
					set_print_color(color);
					set_cursor_visibility(visibility);
					return text;
			}
		}
	}
}