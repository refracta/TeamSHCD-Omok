/**
  @file gameviewutils.c
  @brief 게임 화면 처리간 필요한 유틸 함수들이 구현된 소스 파일
*/
#include "gameviewutils.h"

void init_grd(GameData *data)
{
    data->grd = malloc_grd(GRID_SIZE, GRID_SIZE);

    data->grd->line_color = GRD_LINE_TBCOLOR;
    data->grd->black_color = GRD_BLACK_TBCOLOR;
    data->grd->white_color = GRD_WHITE_TBCOLOR;
    data->grd->cursor_color = GRD_CURSOR_TBCOLOR;
    data->grd->banned_color = GRD_BANNED_TBCOLOR;

    data->grd->x = 1 + 14;
    data->grd->y = 3 + 5;
}

void init_pid(GameData *data)
{
    data->p1id.x = 0 + 14;
    data->p1id.y = 0;
    data->p1id.width = (19 + 15) * 2;
    data->p1id.bar_tbcolor = PI_BAR_TBCOLOR;
    data->p1id.timer.percent = 100;

    data->p1id.player.player_number = 1;
    data->p1id.direction = 0;
    data->p1id.x = 0 + 14;
    data->p1id.y = 0;
    data->p1id.width = (19 + 15) * 2;
    data->p1id.player.win = 1;
    data->p1id.player.lose = 0;
    data->p1id.player.glyph = SG_BLACK;
    data->p1id.glyph_tbcolor = P1_GLYPH_TBCOLOR;
    data->p1id.outline_tbcolor = PI_OUTLINE_TBCOLOR;
    data->p1id.text_tbcolor = PI_TEXT_TBCOLOR;
    data->p1id.player.color = P1_DEFAULT_TBCOLOR;
    data->p1id.timer.left_seconds = TO_SECOND(data->timer_value);

    data->p2id.x = 0 + 14;
    data->p2id.y = 7 + 19;
    data->p2id.width = (19 + 15) * 2;
    data->p2id.bar_tbcolor = PI_DISABLED_BAR_TBCOLOR;
    data->p2id.outline_tbcolor = PI_DISABLED_OUTLINE_TBCOLOR;
    data->p2id.timer.percent = 100;

    data->p2id.player.player_number = 2;
    data->p2id.direction = 1;
    data->p2id.x = 0 + 14;
    data->p2id.y = 7 + 17 + 4;
    data->p2id.width = (19 + 15) * 2;
    data->p2id.player.win = 0;
    data->p2id.player.lose = 1;
    data->p2id.player.glyph = SG_WHITE;
    data->p2id.glyph_tbcolor = P2_GLYPH_TBCOLOR;
    data->p2id.outline_tbcolor = PI_OUTLINE_TBCOLOR;
    data->p2id.text_tbcolor = PI_TEXT_TBCOLOR;
    data->p2id.player.color = P2_DEFAULT_TBCOLOR;
    data->p2id.timer.left_seconds = TO_SECOND(data->timer_value);
}

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