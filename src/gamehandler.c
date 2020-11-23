/**
  @file gamehandler.c
  @brief 게임 핸들러
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
    set_print_color(TO_TBCOLOR(WHITE, BLACK));
    clear_console();
}

/**
 * @brief 인트로 스킵용 키 핸들러
 * @param c getch 반환 값
 * @return 키 핸들러 상수
 */
int skip_intro(int c, void *data)
{
    return 0;
}

/**
 * @brief 인트로 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_intro(GameData *data)
{
    draw_intro(data->tick++);
    if (wait_with_handler(20, skip_intro, NULL) > -1 || data->tick > INTRO_FULL_TICK)
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
    int selection = run_main_menu();
    switch (selection)
    {
        case MM_OMOK:
            change_status(data, GS_GAME);
            break;
        case MM_NMOK:
            xywprintf(49, 18, L"추후지원 예정입니다.");
            wait(1000);
            xywprintf(49, 18, L"                    ");
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
        set_console_size(98, 35);
        run_player_name_prompt(&(data->p1id.player), &(data->p2id.player));
        clear_console();
        draw_game_rule();
        for (int i = 0; i < 8; i++)
        {
            data->msg[i][0] = '\0';
        }
        draw_game_message(data->msg);

        data->grd = malloc_grd(19, 19);


        data->grd->line_color = TO_TBCOLOR(BLACK, YELLOW);
        data->grd->black_color = TO_TBCOLOR(BLACK, YELLOW);
        data->grd->white_color = TO_TBCOLOR(WHITE, YELLOW);
        data->grd->cursor_color = TO_TBCOLOR(LIGHT_GREEN, YELLOW);
        data->grd->banned_color = TO_TBCOLOR(LIGHT_RED, YELLOW);

        //data->grd->grid[10][10] = SG_BLACK;
        data->grd->stone_colors[10][11] = data->grd->black_color;
        data->grd->grid[10][11] = SG_BLACK;
        data->grd->stone_colors[10][12] = data->grd->black_color;
        data->grd->grid[10][12] = SG_BLACK;
        data->grd->stone_colors[11][10] = data->grd->black_color;
        data->grd->grid[11][10] = SG_BLACK;
        data->grd->stone_colors[12][10] = data->grd->black_color;
        data->grd->grid[12][10] = SG_BLACK;

        data->grd->stone_colors[10 + 5][11] = data->grd->black_color;
        data->grd->grid[10 + 5][11] = SG_BLACK;
        data->grd->stone_colors[10 + 5][12] = data->grd->black_color;
        data->grd->grid[10 + 5][12] = SG_BLACK;
        data->grd->stone_colors[10 + 5][13] = data->grd->black_color;
        data->grd->grid[10 + 5][13] = SG_BLACK;
        data->grd->stone_colors[11 + 5][10] = data->grd->black_color;
        data->grd->grid[11 + 5][10] = SG_BLACK;
        data->grd->stone_colors[12 + 5][10] = data->grd->black_color;
        data->grd->grid[12 + 5][10] = SG_BLACK;
        data->grd->stone_colors[13 + 5][10] = data->grd->black_color;
        data->grd->grid[13 + 5][10] = SG_BLACK;

        data->grd->stone_colors[5][10] = data->grd->black_color;
        data->grd->grid[5][10] = SG_BLACK;
        data->grd->stone_colors[5][11] = data->grd->black_color;
        data->grd->grid[5][11] = SG_BLACK;
        data->grd->stone_colors[5][12] = data->grd->black_color;
        data->grd->grid[5][12] = SG_BLACK;
        data->grd->stone_colors[5][13] = data->grd->black_color;
        data->grd->grid[5][13] = SG_BLACK;
        data->grd->stone_colors[5][15] = data->grd->black_color;
        data->grd->grid[5][15] = SG_BLACK;

        data->grd->x = 1 + 14;
        data->grd->y = 3 + 5;

        data->p1id.x = 0 + 14;
        data->p1id.y = 0;
        data->p1id.width = (19 + 15) * 2;
        data->p1id.bar_tbcolor = TO_TBCOLOR(BLACK, WHITE);
        data->p1id.outline_tbcolor = TO_TBCOLOR(WHITE, BLACK);
        data->p1id.timer.left_seconds = 10;
        data->p1id.timer.percent = 100;

        data->p1id.player.player_number = 1;
        data->p1id.direction = 0;
        data->p1id.x = 0 + 14;
        data->p1id.y = 0;
        data->p1id.width = (19 + 15) * 2;
        data->p1id.player.win = 1;
        data->p1id.player.lose = 0;
        data->p1id.player.glyph = SG_BLACK;
        data->p1id.glyph_tbcolor = TO_TBCOLOR(WHITE, BLACK);
        data->p1id.outline_tbcolor = TO_TBCOLOR(WHITE, BLACK);
        data->p1id.text_tbcolor = TO_TBCOLOR(WHITE, BLACK);
        data->p1id.player.color = TO_TBCOLOR(LIGHT_JADE, BLACK);

        draw_player_interface(&data->p1id);

        data->p2id.x = 0 + 14;
        data->p2id.y = 7 + 19;
        data->p2id.width = (19 + 15) * 2;
        data->p2id.bar_tbcolor = TO_TBCOLOR(BLACK, GRAY);
        data->p2id.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
        data->p2id.timer.left_seconds = 10;
        data->p2id.timer.percent = 100;

        data->p2id.player.player_number = 2;
        data->p2id.direction = 1;
        data->p2id.x = 0 + 14;
        data->p2id.y = 7 + 17 + 4;
        data->p2id.width = (19 + 15) * 2;
        data->p2id.player.win = 0;
        data->p2id.player.lose = 1;
        data->p2id.player.glyph = SG_WHITE;
        data->p2id.glyph_tbcolor = TO_TBCOLOR(WHITE, BLACK);
        data->p2id.outline_tbcolor = TO_TBCOLOR(WHITE, BLACK);
        data->p2id.text_tbcolor = TO_TBCOLOR(WHITE, BLACK);
        data->p2id.player.color = TO_TBCOLOR(LIGHT_PURPLE, BLACK);

        draw_player_interface(&data->p2id);

        data->p2id.bar_tbcolor = TO_TBCOLOR(BLACK, WHITE);
        data->p2id.outline_tbcolor = TO_TBCOLOR(WHITE, BLACK);

        data->status_inited = true;
    }

    int player_number = data->tick++ % 2 + 1;

    run_select_stone_position(data, player_number);

    char player_glyph = (player_number == 1 ? data->p1id : data->p2id).player.glyph;
    if (check_winnmok(data->grd->grid, 5, data->grd->width, data->grd->height, data->grd->cursor_x, data->grd->cursor_y,
                      player_glyph))
    {
        add_message_to_list(data->msg, player_glyph == SG_BLACK ? L"흑의 승리입니다." : L"백의 승리입니다.");
        add_message_to_list(data->msg, L"<대국이 끝났습니다>");
        draw_game_message(data->msg);
        //get_key_input();
        //change_status(data, GS_MAIN);
    }
}

/**
 * @brief 도움말 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_help(GameData *data)
{
    xywprintf(38, 10, L"간단한 오목을 즐길 수 있는 프로그램입니다.");
    xywprintf(63, 12, L"SHCD, VERSION 1.0.0");
    xyprintf(46, 17, ASCII_PEOPLE1);
    xyprintf(64, 15, ASCII_PEOPLE2);
    get_key_input();
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
    set_console_title(u8"오목 - SHCD");
    set_default_mode();
    set_cursor_visibility(false);
    set_console_size(CONSOLE_COLS, CONSOLE_LINES);
}

/**
 * @brief 게임을 시작한다.
 */
void start_game()
{
    init_game();
    GameData data;
    change_status(&data, GS_INTRO);
    while (true)
    {
        game_loop(&data);
    }
}