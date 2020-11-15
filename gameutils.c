#include <stdbool.h>
#include "inc/consoleutils.h"
#include "inc/systemutils.h"
#include "inc/interfacerenderer.h"
#include "inc/keycode.h"

int run_menu(MenuData* data, bool disable_escape) {
	draw_menu(data);
	while (true)
	{
		int c = get_key_input();
		if (c == 0xE0 || c == 0) {
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
			if (data->current_index < data->length - 1) {
				data->current_index++;
				draw_menu(data);
			}
			break;
		case UP_KEY:
			if (data->current_index > 0) {
				data->current_index--;
				draw_menu(data);
			}
			break;
		case ENTER_KEY:
			return data->current_index;
			break;
		}
	}
}