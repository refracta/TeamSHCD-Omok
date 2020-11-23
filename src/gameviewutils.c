/**
  @file gameviewutils.c
  @brief 게임 화면 유틸
*/
#include "gameviewutils.h"

int add_message_to_list(wchar_t list[8][BUFSIZ], wchar_t *data)
{
    if (list[8 - 1][0] != '\0')
    {
        for (int i = 0; i < 8 - 1; i++)
        {
            wcscpy(list[i], list[i + 1]);
        }
        wcscpy(list[7], data);
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            if (list[i][0] == '\0')
            {
                wcscpy(list[i], data);
                break;
            }
        }
    }
}

void set_player_interface_to_disable_color(PlayerInterfaceData *copy_id)
{
    copy_id->outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    copy_id->bar_tbcolor = TO_TBCOLOR(BLACK, GRAY);
}