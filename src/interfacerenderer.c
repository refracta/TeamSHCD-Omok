/**
  @file interfacerenderer.c
  @brief 게임 인터페이스 함수들이 구현된 소스 파일
*/

#include "interfacerenderer.h"

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
    xyprintf(title_x, 1, ASCII_TITLE_SHCD);
    xyprintf(title_x, 9, "-----------SeungHapCha Developers----------");

    set_print_color(TO_TBCOLOR(GREEN, BLACK));
    xyprintf(14, 21, ASCII_PEOPLE1);

    set_print_color(TO_TBCOLOR(PURPLE, BLACK));
    xyprintf(24, 24, ASCII_DRUM_CAN);

    set_print_color(TO_TBCOLOR(JADE, BLACK));
    xyprintf(34, 19, ASCII_PEOPLE2);

    set_print_color(TO_TBCOLOR(RED, BLACK));
    if (tick % 12 == 0)
    {
        xyprintf(24, 21, ASCII_SMOKE2);
    }
    else if (tick % 6 == 0)
    {
        xyprintf(24, 21, ASCII_SMOKE1);
    }

    set_print_color(TO_TBCOLOR(BLUE, BLACK));
    int car_start_x = 72;
    if (car_start_x - tick >= 20)
    {
        xyprintf(72 - tick, 10, ASCII_SHC);
        set_cursor_position(position.X, position.Y);
    }
    else
    {
        xyprintf(20, 10, ASCII_SHC);
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
            if (position.Y <= 30 - 1 - 1)
            {
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
void draw_menu(MenuData *data)
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
    wprintf(L"[ %s%*s ]", data->name, max_length - strrlen(data->name), L"");
    set_print_color(data->outline_tbcolor);
    wprintf(L"─┐ ");

    for (int i = 0; i < data->length; i++)
    {
        set_print_color(data->outline_tbcolor);
        xywprintf(data->x, data->y + (i + 1), L"│ ");
        for (int i = 0; i < 8 + max_length - 2; i++)
        {
            wprintf(" ");
        }
        set_cursor_position(data->x + 2, data->y + (i + 1));
        if (i != data->current_index)
        {
            set_print_color(data->non_selected_tbcolor);
        }
        else
        {
            set_print_color(data->selected_tbcolor);
        }
        wprintf(L"   %s%*s   ", data->list[i], max_length - strrlen(data->list[i]), L"");
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
void draw_prompt(PromptData *data)
{
    short color = get_print_color();
    int max_length = MAX(data->rlen, strrlen(data->message));

    set_print_color(data->outline_tbcolor);
    xywprintf(data->x, data->y, L"┌──");
    set_print_color(data->message_tbcolor);
    wprintf(L"[ %s%*s ]", data->message, (int) (max_length - strrlen(data->message)), L"");
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
* @brief 플레이어 인터페이스 정보(타이머 및 플레이어 정보)를 그린다.
* @param data 플레이어 인터페이스 정보 데이터
*/
void draw_player_interface(PlayerInterfaceData *data)
{
    short original_color = get_print_color();

    //outline
    set_print_color(data->outline_tbcolor);
    xywprintf(data->x, data->y, L"┌ ");
    for (int i = 0; i < (data->width - 4); i++)
    {
        wprintf(L"─");
    }
    xywprintf(data->x + (data->width - 2), data->y, L"┐ ");

    for (int i = 1; i <= 5; i++)
    {
        xywprintf(data->x, data->y + i, L"│ ");
        xywprintf(data->x + (data->width - 2), data->y + i, L"│ ");
    }
    xywprintf(data->x, data->y + 6, L"└ ");
    for (int i = 0; i < (data->width - 2); i++)
    {
        xywprintf(data->x + 1 + i, data->y + 6, L"─");
    }
    xywprintf(data->x + (data->width - 2), data->y + 6, L"┘ ");

    //separate line
    int timer_y = 0, timebar_y = 0;
    timer_y = data->direction == 0 ? 4 : 2; // 0 -> 타이머가 아래, 플레이어 정보가 위
    timebar_y = data->direction == 0 ? timer_y + 1 : timer_y - 1;
    xywprintf(data->x, data->y + timer_y, L"├");
    for (int i = 0; i < (data->width - 3); i++)
    {
        wprintf(L"─");
    }
    xywprintf(data->x + (data->width - 2), data->y + timer_y, L"┤");

    //timer shape
    xywprintf(data->x + data->width - 6, data->y + timebar_y, L"│ ");
    int render_seconds = data->timer.left_seconds < 0 ? 0 : data->timer.left_seconds;
    xywprintf(data->x + data->width - 4, data->y + timebar_y, L"%02d", render_seconds);

    set_print_color(TO_TBCOLOR(TO_BACKGROUND_COLOR(data->bar_tbcolor), TO_TEXT_COLOR(data->bar_tbcolor)));
    set_cursor_position(data->x + 2, data->y + timebar_y);
    for (int i = 0; i < (data->width - 8); i++)
    {
        wprintf(L" ");
    }

    set_print_color(data->bar_tbcolor);
    set_cursor_position(data->x + 2, data->y + timebar_y);
    int percent = data->timer.left_seconds < 0 ? 100 : data->timer.percent;
    for (int i = 0; i < (int) (((data->width - 8) * (double) percent / 100.0)); i++)
    {
        wprintf(L" ");
    }

    //player info
    int info_y = data->direction == 0 ? 0 : 2;
    set_print_color(data->text_tbcolor);
    xywprintf(data->x + 2, data->y + 1 + info_y, L"Player %d", data->player.player_number);
    xywprintf(data->x + 2, data->y + 2 + info_y, data->player.name);
    xywprintf(data->x + 2, data->y + 3 + info_y, L"W/L %d/%d", data->player.win, data->player.lose);

    set_print_color(data->glyph_tbcolor);
    xywprintf((data->x + data->width) - 8, data->y + 1 + info_y,
              data->player.glyph == SG_BLACK ? RG_BLACK : RG_WHITE);

    set_print_color(data->player.color);
    xywprintf((data->x + data->width) - 5, data->y + 1 + info_y, L"■");

    set_cursor_position(0, 0);
    set_print_color(original_color);
}