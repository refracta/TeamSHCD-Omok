/**
  @file gameviewrenderer.c
  @brief 게임 화면 실행
*/
#include "gameviewrunner.h"

int handle_ssp_key_input(int c, void *param)
{
    void **list = (void **) param;
    GameData *data = (GameData *) list[0];
    GridRenderData *grd = data->grd;
    PlayerInterfaceData *pid = (PlayerInterfaceData *) list[1];

    switch (c)
    {
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

            if (grd->grid[grd->cursor_x][grd->cursor_y] == SG_EMPTY)
            {
                bool is_double_three = !check_double_three(grd->grid, grd->width, grd->height, grd->cursor_x,
                                                           grd->cursor_y, pid->player.glyph);
                bool is_double_four = !check_double_four(grd->grid, grd->width, grd->height, grd->cursor_x,
                                                         grd->cursor_y, pid->player.glyph);
                bool is_overline = !check_overline(grd->grid, grd->width, grd->height, grd->cursor_x, grd->cursor_y,
                                                   pid->player.glyph);
                if (is_double_three)
                {
                    add_message_to_list(data->msg, L"쌍삼인 자리입니다.");
                    draw_game_message(data->msg);
                    FA_S(OCTAVE_6, 20);
                    FA_S(OCTAVE_6, 20);
                }
                else if (is_double_four)
                {
                    add_message_to_list(data->msg, L"쌍사인 자리입니다.");
                    draw_game_message(data->msg);
                    FA_S(OCTAVE_6, 20);
                    FA_S(OCTAVE_6, 20);
                }
                else if (is_overline)
                {
                    add_message_to_list(data->msg, L"장목인 자리입니다.");
                    draw_game_message(data->msg);
                    FA_S(OCTAVE_6, 20);
                    FA_S(OCTAVE_6, 20);
                }
                else
                {
                    grd->grid[grd->cursor_x][grd->cursor_y] = pid->player.glyph;
                    grd->stone_colors[grd->cursor_x][grd->cursor_y] = (pid->player.glyph == SG_BLACK ? grd->black_color
                                                                                                     : grd->white_color);
                    draw_grid(grd);
                    RA(OCTAVE_4, 20);
                    return 0;
                }
            }
            else
            {
                add_message_to_list(data->msg, L"이미 돌이 있습니다.");
                draw_game_message(data->msg);
                FA_S(OCTAVE_6, 20);
                FA_S(OCTAVE_6, 20);
            }
            break;
    }
    draw_select_stone(grd);
    return -1;
}

void run_select_stone_position(GameData *data, int player_number)
{
    PlayerInterfaceData *id;
    if (player_number == 1)
    {
        id = &data->p1id;
    }
    else if (player_number == 2)
    {
        id = &data->p2id;
    }
    else
    {
        id = NULL;
    }
    add_message_to_list(data->msg, id->player.glyph == SG_BLACK ? L"흑의 차례입니다." : L"백의 차례입니다.");
    draw_game_message(data->msg);
    PlayerInterfaceData copy_id;
    memcpy(&copy_id, id, sizeof(PlayerInterfaceData));
    draw_player_interface(id);
    draw_select_stone(data->grd);
    void *param[] = {data, id};
    int original_seconds = copy_id.timer.left_seconds;
    for (int i = 0; i < original_seconds; i++,
            copy_id.timer.left_seconds--,
            copy_id.timer.percent = ((double) copy_id.timer.left_seconds / id->timer.left_seconds) * 100)
    {
        draw_player_interface(&copy_id);
        int status = wait_with_handler(1000, handle_ssp_key_input, param);
        if (status > -1)
        {
            set_player_interface_to_disable_color(&copy_id);
            draw_player_interface(&copy_id);
            add_message_to_list(data->msg, id->player.glyph == SG_BLACK ? L"흑이 놓여졌습니다." : L"백이 놓여졌습니다");

            wchar_t position_text[BUFSIZ];
            swprintf(position_text, BUFSIZ, L"좌표 (%d, %d)", data->grd->cursor_x + 1,
                     data->grd->height - data->grd->cursor_y);

            //wprintf(L"%s", position_text);
            add_message_to_list(data->msg, position_text);
            draw_game_message(data->msg);
            //xywprintf(2, 4, L"%s이 수를 두었습니다.", player_glyph == SG_BLACK ? L"흑": L"백");
            return;
        }
    }
    set_player_interface_to_disable_color(&copy_id);
    draw_player_interface(&copy_id);
    add_message_to_list(data->msg, id->player.glyph == SG_BLACK ? L"흑의 시간 초과" : L"백의 시간 초과");
    draw_game_message(data->msg);
    //xywprintf(2, 5, L"시간 초과로 %s의 턴이 넘어갑니다.", player_glyph == SG_BLACK ? L"흑": L"백");
    return;
}

void run_player_name_prompt(PlayerData *player1, PlayerData *player2)
{
    PromptData prompt;
    prompt.message = L"Player1의 이름을 입력하세요";
    prompt.x = 27;
    prompt.y = 16;
    prompt.rlen = 30;
    prompt.outline_tbcolor = TO_TBCOLOR(LIGHT_JADE, BLACK);
    prompt.text_tbcolor = TO_TBCOLOR(LIGHT_JADE, BLACK);
    prompt.message_tbcolor = TO_TBCOLOR(BLACK, WHITE);
    wchar_t *player1_name = run_prompt(&prompt);
    wcscpy(player1->name, player1_name);
    free(player1_name);
    prompt.message = L"Player2의 이름을 입력하세요";
    prompt.outline_tbcolor = TO_TBCOLOR(LIGHT_PURPLE, BLACK);
    prompt.text_tbcolor = TO_TBCOLOR(LIGHT_PURPLE, BLACK);
    prompt.message_tbcolor = TO_TBCOLOR(BLACK, WHITE);
    wchar_t *player2_name = run_prompt(&prompt);
    wcscpy(player2->name, player2_name);
    free(player2_name);
}

/**
 * @brief 메인 화면 메뉴를 실행한다.
 * @param 선택한 메뉴 색인
 */
int run_main_menu()
{
    MenuData menu;
    menu.name = L" 메뉴";
    wchar_t **list = malloc(sizeof(wchar_t *) * 4);
    list[0] = L" 오목";
    list[1] = L" N목";
    list[2] = L"도움말";
    list[3] = L"나가기";
    menu.list = list;
    menu.length = 4;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(JADE, LIGHT_RED);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, GRAY);

    menu.x = 51;
    menu.y = 19;

    int index = run_menu(&menu, true);
    free(list);
    return index;
}