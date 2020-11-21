/**
  @file gameutils.c
  @brief 게임 유틸
*/
#include <stdbool.h>
#include <locale.h>
#include "inc/consoleutils.h"
#include "inc/systemutils.h"
#include "inc/interfacerenderer.h"
#include "inc/gamerenderer.h"
#include "inc/keycode.h"
#include "inc/gamecore.h"


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
		switch (c) {
		case ESCAPE_KEY:
			if (!disable_escape)
			{
				return -1;
			}
			break;
		case DOWN_KEY:
				data->current_index = data->current_index + 1 < data->length ? data->current_index + 1 : 0;
				draw_menu(data);
				Beep(349 * 2, 100);
			break;
		case UP_KEY:
				data->current_index = data->current_index > 0 ? data->current_index - 1 : data->length - 1;
				draw_menu(data);
				Beep(349 * 2, 100);
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

void select_stone_position(GridRenderData* grd, char player_glyph)
{
	while (true)
	{
		draw_grid(grd);
		if(grd->grid[grd->cursor_x][grd->cursor_y] != SG_EMPTY){
            coloring_stone(grd->x, grd->y, grd->cursor_x, grd->cursor_y, SG_BANNED, grd->banned_color);
		}else{
            coloring_stone(grd->x, grd->y, grd->cursor_x, grd->cursor_y, SG_CURSOR, grd->cursor_color);
		}
		int c = get_key_input();
		switch (c) {
		case UP_KEY:
			grd->cursor_y = grd->cursor_y > 0 ? grd->cursor_y - 1 : grd->height - 1;
			break;
		case DOWN_KEY:
			grd->cursor_y = grd->cursor_y + 1 < grd->height ? grd->cursor_y + 1 : 0;
			break;
		case RIGHT_KEY:
			grd->cursor_x = grd->cursor_x + 1 < grd->width ? grd->cursor_x + 1 : 0;
			break;
		case LEFT_KEY:
			grd->cursor_x = grd->cursor_x > 0 ? grd->cursor_x - 1 : grd->width - 1;
			break;
		case SPACE_KEY:
		case ENTER_KEY:
            if(grd->grid[grd->cursor_x][grd->cursor_y] == SG_EMPTY){
                grd->grid[grd->cursor_x][grd->cursor_y] = player_glyph;
                grd->stone_colors[grd->cursor_x][grd->cursor_y] = (player_glyph == SG_BLACK ? grd->black_color : grd->white_color);
                draw_grid(grd);
                Beep(450, 20);
                return;
            }else{
				Beep(494 * 3, 20);
				Beep(494 * 3, 20);
            }
			break;
		}
	}
}
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
			int c = get_key_input();
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
