/**
  @file gamehandler.c
  @brief 게임을 핸들링하는 중요 함수들이 구현된 소스 파일
*/
#include "gamehandler.h"

/**
 * @brief 현재 게임의 상태를 변경합니다. 게임 데이터의 상태 변수를 변경하고, 상태 변경시의 초기화 작업을 수행한다.
 * @param data 게임 데이터 구조체의 포인터
 * @param data 게임 상태 열거형
 */
void change_status(GameData *data, GameStatus status)
{
    if (data->status == GS_INTRO && status != GS_INTRO)
    {
        set_default_mode();
    }
    else if (status == GS_INTRO)
    {
        set_boost_mode();
    }

    data->status = status;
    data->status_inited = false;
    data->tick = 0;
    data->turn = 1;
    set_print_color(DEFAULT_TBCOLOR);
    clear_console();
}

/**
 * @brief 인트로 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_intro(GameData *data)
{
    draw_intro(data->tick++);
    if (wait_with_handler(20, NULL, NULL) != -1 || data->tick > INTRO_FULL_TICK)
    {
        change_status(data, GS_MAIN);
    }
}

/**
 * @brief 메인 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_main(GameData *data)
{
    if (!data->status_inited)
    {
        set_console_size(CONSOLE_COLS, CONSOLE_LINES);
        data->status_inited = true;
    }
    xyprintf(30, 1, ASCII_OMOK);
    MainMenu selection = run_main_menu();
    switch (selection)
    {
        case MM_OMOK:
            data->nmok_mode = false;
            change_status(data, GS_GAME);
            break;
        case MM_NMOK:
            data->nmok_mode = true;
            change_status(data, GS_GAME);
            break;
        case MM_RANKING:
            change_status(data, GS_RANKING);
            break;
        case MM_HELP:
            change_status(data, GS_HELP);
            break;
        case MM_EXIT:
            exit(0);
            break;
    }
}

/**
 * @brief 게임 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_game(GameData *data)
{
    if (!data->status_inited)
    {
        if (!data->regame)
        {
            set_console_size(GAME_VIEW_COLS, GAME_VIEW_LINES);
            if (data->nmok_mode)
            {
                data->victory_condition = run_select_nmok_menu();
                clear_console();
            }
            else
            {
                data->victory_condition = 5;
            }
            run_player_name_prompt(&(data->p1id.player), &(data->p2id.player));
            clear_console();
            TimerValue timer_value = run_select_timer_time_menu();
            clear_console();
            data->timer_value = timer_value;
            data->dump_string = (wchar_t *) calloc(BUFSIZ, sizeof(wchar_t));
            swprintf(data->dump_string, BUFSIZ * (data->turn), L"[%s] vs [%s]\n\n", data->p1id.player.name,
                     data->p2id.player.name);
        }

        init_grd(data);
        init_pid(data);
        draw_player_interface(&data->p1id);
        draw_player_interface(&data->p2id);
        update_position_message(2, 10, 10, 1);
        data->p2id.bar_tbcolor = PI_BAR_TBCOLOR;
        data->p2id.outline_tbcolor = PI_OUTLINE_TBCOLOR;

        draw_game_rule(data->victory_condition, TO_TIME_STRING(data->timer_value));

        for (int i = 0; i < 8; i++)
        {
            data->msg[i][0] = '\0';
        }
        draw_game_message(data->msg);

        data->status_inited = true;
    }

    int player_number = (data->turn++ % 2) ? 1 : 2;
    /*
     * 1 -> P1 , mod(1, 2) = 1
     * 2 -> P2 , mod(2, 2) = 0
     * 3 -> P1 , mod(3, 2) = 1
     * 4 -> P2 , mod(4, 2) = 0
     * */

    run_select_stone_position(data, player_number);

    char player_glyph = (player_number == 1 ? data->p1id : data->p2id).player.glyph;
    char player_color = (player_number == 1 ? data->p1id : data->p2id).player.color;
    player_color = TO_TBCOLOR(TO_TEXT_COLOR(player_color), YELLOW);
    if (check_all_conditions(data->grd->grid, data->victory_condition, data->grd->width, data->grd->height,
                             data->grd->cursor_x, data->grd->cursor_y,
                             player_glyph, CHECK_WIN))
    {
        add_message_to_list(data->msg, player_glyph == SG_BLACK ? L"흑의 승리입니다." : L"백의 승리입니다.");

        add_message_to_list(data->msg, L"<대국이 끝났습니다>");
        add_message_to_list(data->msg, L"(r)egame");
        add_message_to_list(data->msg, L"(b)ack to main");
        add_message_to_list(data->msg, L"(s)ave game dump");

        append_rank(player_glyph == SG_BLACK ? data->p1id.player.name : data->p2id.player.name,
                    player_glyph == SG_BLACK ? data->p2id.player.name : data->p1id.player.name);

        data->dump_string = (wchar_t *) realloc(data->dump_string, sizeof(wchar_t) * BUFSIZ *
                                                                   (data->turn)); //턴당 wchar_t 크기를 버퍼사이즈만큼 메모리 할당
        swprintf(data->dump_string, BUFSIZ * (data->turn), L"%s\n%s의 승리입니다!\n소요 턴 수: %d", data->dump_string,
                 player_glyph == SG_BLACK ? L"흑" : L"백", data->turn - 1);

        draw_game_message(data->msg);

        run_win_line_blink(data->grd, data->victory_condition, player_glyph, player_color, 5, 100);

        VICTORY_FANFARE();

        bool is_saved = false;
        while (true)
        {
            char c = get_key_input();
            switch (c)
            {
                case 'r':
                case 'R':
                    free_grd(data->grd);
                    free(data->dump_string);
                    data->dump_string = (wchar_t *) calloc(BUFSIZ, sizeof(wchar_t));
                    data->regame = true;
                    change_status(data, GS_GAME);
                    return;
                case 'b':
                case 'B':
                    free_grd(data->grd);
                    free(data->dump_string);
                    data->dump_string = (wchar_t *) calloc(BUFSIZ, sizeof(wchar_t));
                    data->regame = false;
                    change_status(data, GS_MAIN);
                    return;
                case 's':
                case 'S':
                    if (is_saved == true)
                    {
                        continue;
                    }
                    make_dump(data->dump_string, data);
                    add_message_to_list(data->msg, L"덤프 저장 완료!");
                    add_message_to_list(data->msg, L"(r)egame");
                    add_message_to_list(data->msg, L"(b)ack to main");
                    draw_game_message(data->msg);
                    is_saved = true;
            }
        }
    }
}

/**
 * @brief 랭킹 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_ranking(GameData *data)
{
    print_ranking();

    get_key_input();
    change_status(data, GS_MAIN);
}

/**
 * @brief 도움말 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_help(GameData *data)
{
    xywprintf(5, 3, HELP_TEXT);
    set_print_color(TO_TBCOLOR(YELLOW, BLACK));
    xywprintf(38, 17, L"간단한 오목을 즐길 수 있는 프로그램입니다.");
    xywprintf(60, 18, L"SHCD, VERSION 1.2.2");
    set_print_color(TO_TBCOLOR(GREEN, BLACK));
    xyprintf(46, 22, ASCII_PEOPLE1);
    set_print_color(TO_TBCOLOR(JADE, BLACK));
    xyprintf(64, 20, ASCII_PEOPLE2);

    get_key_input();
    for (int i = 0; i < 10; i++)
    {
        set_print_color(TO_TBCOLOR(rand() % (NUMBER_OF_COLOR - 1) + 1, BLACK));
        xyprintf(46, 22, ASCII_PEOPLE1);
        set_print_color(TO_TBCOLOR(rand() % (NUMBER_OF_COLOR - 1) + 1, BLACK));
        xyprintf(64, 20, ASCII_PEOPLE2);
        if (wait_with_handler(100, NULL, NULL) != -1)
        {
            break;
        }
    }
    change_status(data, GS_MAIN);
}

/**
 * @brief 게임 루프를 처리한다.
 */
void game_loop(GameData *data)
{
    switch (data->status)
    {
        case GS_INTRO:
            run_intro(data);
            break;
        case GS_MAIN:
            run_main(data);
            break;
        case GS_GAME:
            run_game(data);
            break;
        case GS_RANKING:
            run_ranking(data);
            break;
        case GS_HELP:
            run_help(data);
            break;
    }
}

/**
 * @brief 게임 시작시 초기화 작업을 진행한다.
 */
void init_game()
{
    set_encoding_utf8();
    set_console_title(u8"TeamSHCD - 오목");
    set_default_mode();
    set_cursor_visibility(false);
    set_console_size(CONSOLE_COLS, CONSOLE_LINES);
}

/**
 * @brief 게임 시작시 데이터 초기화 작업을 진행한다.
 */
void init_game_data(GameData *data)
{
    data->regame = false;
    srand(time(NULL));
}

/**
 * @brief 게임을 시작한다.
 */
void start_game()
{
    init_game();
    GameData data;
    init_game_data(&data);
    change_status(&data, GS_INTRO);
    while (true)
    {
        game_loop(&data);
    }
}