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
		}
	}
}