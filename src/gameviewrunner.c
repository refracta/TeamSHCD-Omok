/**
  @file gameviewrunner.c
  @brief 게임 화면과 함께 인게임 이벤트 핸들링에 관련된 함수들이 구현된 소스 파일
*/
#include "gameviewrunner.h"

/**
 * @brief select_stone_position 내부에서 호출되는 키 핸들러
 * @param c key value
 * @param param 자유형 매개변수 포인터
 */
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
                CheckResult result = data->victory_condition == 5 ? check_confirm_omok(grd->grid, grd->width,
                                                                                       grd->height, grd->cursor_x,
                                                                                       grd->cursor_y, pid->player.glyph)
                                                                  : PLACE_VALID;
                switch (result)
                {
                    case PLACE_VALID:
                        grd->grid[grd->cursor_x][grd->cursor_y] = pid->player.glyph;
                        grd->stone_colors[grd->cursor_x][grd->cursor_y] = (pid->player.glyph == SG_BLACK
                                                                           ? grd->black_color
                                                                           : grd->white_color);
                        draw_grid(grd);

                        update_position_message(data->turn + 1, data->grd->cursor_x + 1,
                                                data->grd->height - data->grd->cursor_y, pid->player.player_number - 1);

                        data->dump_string = (wchar_t *) realloc(data->dump_string, sizeof(wchar_t) * BUFSIZ *
                                                                                   (data->turn)); //턴당 wchar_t 크기를 버퍼사이즈만큼 메모리 할당
                        swprintf(data->dump_string, BUFSIZ * (data->turn), L"%s%s %2d수  (%2d, %2d)\n",
                                 data->dump_string, pid->player.player_number == 1 ? L"흑" : L"백", data->turn - 1,
                                 data->grd->cursor_x + 1, data->grd->height - data->grd->cursor_y);

                        RA(OCTAVE_4, 20);
                        return 0;
                        break;
                    case PLACE_33:
                        add_message_to_list(data->msg, L"쌍삼인 자리입니다.");
                        draw_game_message(data->msg);
                        FA_S(OCTAVE_6, 20);
                        FA_S(OCTAVE_6, 20);
                        break;
                    case PLACE_44:
                        add_message_to_list(data->msg, L"쌍사인 자리입니다.");
                        draw_game_message(data->msg);
                        FA_S(OCTAVE_6, 20);
                        FA_S(OCTAVE_6, 20);
                        break;
                    case PLACE_OVERLINE:
                        add_message_to_list(data->msg, L"장목인 자리입니다.");
                        draw_game_message(data->msg);
                        FA_S(OCTAVE_6, 20);
                        FA_S(OCTAVE_6, 20);
                        break;
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

    update_position_message(data->turn, data->grd->cursor_x + 1, data->grd->height - data->grd->cursor_y,
                            pid->player.player_number);
    draw_select_stone(grd);
    return -1;
}

/**
 * @brief 돌 선택 인터페이스를 실행한다.
 * @param data 게임 데이터
 * @param player_number 플레이어 번호
 */
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
    int original_seconds = id->timer.left_seconds;
    for (int i = 0; i < original_seconds || id->timer.left_seconds == -1; i++,
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
            update_position_message(data->turn + 1, data->grd->cursor_x + 1, data->grd->height - data->grd->cursor_y,
                                    copy_id.player.player_number - 1);
            return;
        }
    }
    set_player_interface_to_disable_color(&copy_id);
    draw_player_interface(&copy_id);
    add_message_to_list(data->msg, id->player.glyph == SG_BLACK ? L"흑의 시간 초과" : L"백의 시간 초과");

    data->dump_string = (wchar_t *) realloc(data->dump_string,
                                            sizeof(wchar_t) * BUFSIZ * (data->turn)); //턴당 wchar_t 크기를 버퍼사이즈만큼 메모리 할당
    swprintf(data->dump_string, BUFSIZ * (data->turn), L"%s%s %2d수  시간초과로 인해 착수하지 못했습니다.\n", data->dump_string,
             copy_id.player.player_number == 1 ? L"흑" : L"백", data->turn - 1);

    update_position_message(data->turn + 1, data->grd->cursor_x + 1, data->grd->height - data->grd->cursor_y,
                            copy_id.player.player_number - 1);
    draw_game_message(data->msg);
    //xywprintf(2, 5, L"시간 초과로 %s의 턴이 넘어갑니다.", player_glyph == SG_BLACK ? L"흑": L"백");
    return;
}

/**
 * @brief 플레이어 이름을 묻는 프로프트를 실행하고 이름 값을 초기화합니다.
 */
void run_player_name_prompt(PlayerData *player1, PlayerData *player2)
{
    PromptData prompt;
    prompt.message = L"Player 1의 이름을 입력하세요";
    prompt.x = 30;
    prompt.y = 16;
    prompt.rlen = 12;
    prompt.outline_tbcolor = TO_TBCOLOR(LIGHT_JADE, BLACK);
    prompt.text_tbcolor = TO_TBCOLOR(LIGHT_JADE, BLACK);
    prompt.message_tbcolor = TO_TBCOLOR(BLACK, WHITE);
    wchar_t *player1_name = run_prompt(&prompt);
    wcscpy(player1->name, player1_name);
    free(player1_name);
    prompt.message = L"Player 2의 이름을 입력하세요";
    prompt.outline_tbcolor = TO_TBCOLOR(LIGHT_PURPLE, BLACK);
    prompt.text_tbcolor = TO_TBCOLOR(LIGHT_PURPLE, BLACK);
    prompt.message_tbcolor = TO_TBCOLOR(BLACK, WHITE);
    wchar_t *player2_name = run_prompt(&prompt);
    wcscpy(player2->name, player2_name);
    free(player2_name);
}

/**
 * @brief 타이머 설정 메뉴를 실행한다.
 * @return 타이머 열거형 값
 */
TimerValue run_select_timer_time_menu()
{
    MenuData menu;
    menu.name = L"타이머 시간";
    wchar_t **list = malloc(sizeof(wchar_t *) * 4);
    list[0] = L"   10초";
    list[1] = L"   20초";
    list[2] = L"   30초";
    list[3] = L"   무한";
    menu.list = list;
    menu.length = 4;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(LIGHT_JADE, LIGHT_PURPLE);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, GRAY);

    menu.x = 38;
    menu.y = 15;

    int index = run_menu(&menu, true);
    free(list);
    return index;
}

/**
 * @brief 메인 화면 메뉴를 실행한다.
 * @return 선택한 메뉴 색인
 */
MainMenu run_main_menu()
{
    MenuData menu;
    menu.name = L" 메뉴";
    wchar_t **list = malloc(sizeof(wchar_t *) * 5);
    list[0] = L" 오목";
    list[1] = L"  N목";
    list[2] = L" 랭킹";
    list[3] = L"도움말";
    list[4] = L"나가기";
    menu.list = list;
    menu.length = 5;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(LIGHT_JADE, LIGHT_PURPLE);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, GRAY);

    menu.x = 51;
    menu.y = 19;

    int index = run_menu(&menu, true);
    free(list);
    return index;
}

/**
 * @brief N목 선택 화면을 실행한다
 * @return 선택한 승리 조건
 */
int run_select_nmok_menu()
{
    MenuData menu;
    menu.name = L" 조건 ";
    wchar_t **list = malloc(sizeof(wchar_t *) * 6);
    list[0] = L"  4목";
    list[1] = L"  6목";
    list[2] = L"  7목";
    list[3] = L"  8목";
    list[4] = L"  9목";
    list[5] = L" 10목";
    menu.list = list;
    menu.length = 6;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(LIGHT_JADE, LIGHT_PURPLE);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, GRAY);

    menu.x = 40;
    menu.y = 14;

    int index = run_menu(&menu, true);
    free(list);
    return index + 4 + (index > 0);
}

/**
 * @brief 이긴 줄을 점멸합니다.
 * @param grid 격자 렌더 데이터
 * @param player_glyph 플레이어 SimpleGlyph
 * @param blink_color 점멸할 색
 * @param number 점멸 횟수
 * @param wait_time 점멸간 대기 시간 (MS)
 */
void run_win_line_blink(GridRenderData *grd, int victory_condition, char player_glyph, short blink_color, int number,
                        int wait_time)
{
    int **win_line = get_win_line(grd->grid, victory_condition, grd->width, grd->height,
                                  player_glyph);
    for (int j = 0; j < number; j++)
    {
        for (int i = 0; i < victory_condition; i++)
        {
            coloring_stone(grd->x, grd->y, win_line[i][0], win_line[i][1], player_glyph, blink_color);
        }
        wait(wait_time);
        for (int i = 0; i < victory_condition; i++)
        {
            coloring_stone(grd->x, grd->y, win_line[i][0], win_line[i][1], player_glyph,
                           player_glyph == SG_BLACK ? grd->black_color : grd->white_color);
        }
        wait(wait_time);
    }
    free(win_line);
}

/**
 * @brief 현재 커서의 위치를 풀력해줍니다.
 * @param turn 현재 턴 수
 * @param x 커서의 x좌표
 * @param y 커서의 y좌표
 * @param player_number 현재 턴 중인 플레이어
 */
void update_position_message(int turn, int x, int y, int player_number)
{
    MenuData data;
    data.x = 53;
    data.y = 14;
    wchar_t **list = malloc(sizeof(wchar_t *) * 4);
    wchar_t text[BUFSIZ];
    swprintf(text, BUFSIZ, L" %s %2d수  (%2d, %2d)", player_number == 1 ? L"흑" : L"백", turn - 1, x, y);
    list[0] = text;
    data.name = L"        위치       ";
    data.list = list;
    data.length = 1;
    data.current_index = 0;
    data.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    data.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    data.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    data.selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    data.non_selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);

    draw_menu(&data);
    free(list);

}

/**
 * @brief 랭킹 출력
*/
void print_ranking()
{
    RankedPlayer player[BUFSIZ] = {-1};
    FILE *stream = fopen("winData.omok", "r+");
    wchar_t *tempbuf;

    if (stream == NULL)
    {
        xywprintf(50, 10, L"아직 랭킹이 없습니다!");
        return;
    }

    wchar_t buf[BUFSIZ];
    int index = 0;
    while (!feof(stream))
    {
        fwscanf(stream, L"%s %04d", player[index].name, &player[index].win);
        index++;
    }
    index--;
    fclose(stream);

    for (int i = 0; i < index; i++)
    {
        player[i].rank = 1;
        for (int j = 0; j < index; j++)
        {
            if (player[i].win < player[j].win)
            {
                player[i].rank++;
            }
        }
    }

    ascending(player, index);
    set_print_color(TO_TBCOLOR(BLACK, LIGHT_YELLOW));
    xywprintf(52, 4, L" 명 예 의   전 당 ");
    set_print_color(TO_TBCOLOR(WHITE, BLACK));
    xywprintf(43, 6, L"순위");
    xywprintf(43, 6, L"순위");
    xywprintf(49, 6, L"닉네임");
    xywprintf(75, 6, L"승리");
    if (index > 9)
    {
        index = 9;
    }
    short origin_color = get_print_color();
    for (int i = 0; i < index; i++)
    {
        if (player[i].rank <= 3)
        {
            set_print_color(14);
        }
        else
        {
            set_print_color(origin_color);
        }
        xywprintf(43, 9 + i * 2, L"%2d위: ", player[i].rank);
        xywprintf(49, 9 + i * 2, player[i].name);
        xywprintf(75, 9 + i * 2, L"%d회", player[i].win);
    }
}