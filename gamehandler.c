/**
  @file gamehandler.c
  @brief 게임 핸들러
*/
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <wchar.h>

#include "inc/gamehandler.h"
#include "inc/consoleutils.h"
#include "inc/systemutils.h"
#include "inc/interfacerenderer.h"
#include "inc/environment.h"
#include "inc/gameutils.h"
#include "inc/gamecore.h"
#include "inc/gamerenderer.h"
#include "inc/keycode.h"

/**
 * @brief 게임이 가지는 상황 열거형
 */
typedef enum
{
    GS_INTRO, GS_MAIN, GS_GAME, GS_HELP
} GameStatus;

/**
 * @brief 게임에서 사용하는 데이터들을 포함하는 구조체
 */
typedef struct
{
    GameStatus status;
    PlayerInterfaceData p1id;
    PlayerInterfaceData p2id;
    wchar_t msg[8][BUFSIZ];
    GridRenderData *grd;
    bool status_inited;
    int tick;
} GameData;

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
 * @brief 메인 화면 메뉴 열거형
 */
typedef enum
{
    MM_OMOK = 0, MM_NMOK, MM_HELP, MM_EXIT
} MainMenu;


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

void *run_player_name_prompt(PlayerData *player1, PlayerData *player2)
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

int draw_game_rule()
{

    MenuData menu;
    menu.name = L"       규칙";
    wchar_t **list = malloc(sizeof(wchar_t *) * 7);
    list[0] = L"승리 조건: 5개의 돌";
    list[1] = L"장목: 금지";
    list[2] = L"흑의 3x3: 금지";
    list[3] = L"시간 제한 20초";
    list[4] = L"";
    list[5] = L"착수 금지: 표시함";
    list[6] = L"오목판: 19x19";
    menu.list = list;
    menu.length = 7;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);

    menu.x = 39 + 14;
    menu.y = 5 + 3;
    draw_menu(&menu);

    //int index = run_menu(&menu, true);
    free(list);
    //return index;
}

int draw_game_message(wchar_t list[8][BUFSIZ])
{
    MenuData menu;
    menu.name = L"       메시지      ";
    wchar_t **copy_list = (wchar_t **) malloc_double_pointer(sizeof(wchar_t), 8, BUFSIZ);
    for (int i = 0; i < 8; i++)
    {
        wcscpy(copy_list[i], list[i]);
    }
    menu.list = copy_list;
    menu.length = 8;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);

    menu.x = 39 + 14;
    menu.y = 17;

    draw_menu(&menu);

//    int index = run_menu(&menu, true);
    free_double_pointer(copy_list, 8);
    //   return index;
}

int add_game_message_with_draw(wchar_t list[8][BUFSIZ], wchar_t *data)
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
    draw_game_message(list);
}

void render_select_stone(GridRenderData *grd)
{
    draw_grid(grd);
    if (grd->grid[grd->cursor_x][grd->cursor_y] != SG_EMPTY)
    {
        coloring_stone(grd->x, grd->y, grd->cursor_x, grd->cursor_y, SG_BANNED, grd->banned_color);
    }
    else
    {
        coloring_stone(grd->x, grd->y, grd->cursor_x, grd->cursor_y, SG_CURSOR, grd->cursor_color);
    }
}

int key_handler(int c, void *param)
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
                    add_game_message_with_draw(data->msg, L"쌍삼인 자리입니다.");
                    Beep(494 * 3, 20);
                    Beep(494 * 3, 20);
                }
                else if (is_double_four)
                {
                    add_game_message_with_draw(data->msg, L"쌍사인 자리입니다.");
                    Beep(494 * 3, 20);
                    Beep(494 * 3, 20);
                }
                else if (is_overline)
                {
                    add_game_message_with_draw(data->msg, L"장목인 자리입니다.");
                    Beep(494 * 3, 20);
                    Beep(494 * 3, 20);
                }
                else
                {
                    grd->grid[grd->cursor_x][grd->cursor_y] = pid->player.glyph;
                    grd->stone_colors[grd->cursor_x][grd->cursor_y] = (pid->player.glyph == SG_BLACK ? grd->black_color
                                                                                                     : grd->white_color);
                    draw_grid(grd);
                    Beep(450, 20);
                    return 0;
                }
            }
            else
            {
                add_game_message_with_draw(data->msg, L"이미 돌이 있습니다.");
                Beep(494 * 3, 20);
                Beep(494 * 3, 20);
            }
            break;
    }
    render_select_stone(grd);
    return -1;
}

void set_interface_disabled(PlayerInterfaceData *copy_id)
{
    copy_id->outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    copy_id->bar_tbcolor = TO_TBCOLOR(BLACK, GRAY);
    //copy_timer->left_seconds = 10;
    //copy_timer->percent = 100;
    draw_player_interface(copy_id);
}

void select_stone_position(GameData *data, int player_number)
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
    add_game_message_with_draw(data->msg, id->player.glyph == SG_BLACK ? L"흑의 차례입니다." : L"백의 차례입니다.");
    PlayerInterfaceData copy_id;
    memcpy(&copy_id, id, sizeof(PlayerInterfaceData));
    draw_player_interface(id);
    render_select_stone(data->grd);
    void *param[] = {data, id};
    int original_seconds = copy_id.timer.left_seconds;
    for (int i = 0; i < original_seconds; i++,
            copy_id.timer.left_seconds--,
            copy_id.timer.percent = ((double) copy_id.timer.left_seconds / id->timer.left_seconds) * 100)
    {
        draw_player_interface(&copy_id);
        int status = wait_with_handler(1000, key_handler, param);
        if (status > -1)
        {
            set_interface_disabled(&copy_id);
            add_game_message_with_draw(data->msg, id->player.glyph == SG_BLACK ? L"흑이 놓여졌습니다." : L"백이 놓여졌습니다");
            wchar_t position_text[BUFSIZ];
            swprintf(position_text, BUFSIZ, L"좌표 (%d, %d)", data->grd->cursor_x + 1,
                     data->grd->height - data->grd->cursor_y);

            //wprintf(L"%s", position_text);
            add_game_message_with_draw(data->msg, position_text);
            //xywprintf(2, 4, L"%s이 수를 두었습니다.", player_glyph == SG_BLACK ? L"흑": L"백");
            return;
        }
    }
    set_interface_disabled(&copy_id);
    add_game_message_with_draw(data->msg, id->player.glyph == SG_BLACK ? L"흑의 시간 초과" : L"백의 시간 초과");
    //xywprintf(2, 5, L"시간 초과로 %s의 턴이 넘어갑니다.", player_glyph == SG_BLACK ? L"흑": L"백");
    return;
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

    // xywprintf(0, 1, L"Player1: %s (Black)", data->player1_data.name);
    // xywprintf(0, 2, L"Player2: %s (White)", data->player2_data.name);
    // xywprintf(0, 3, L"Turn: %d", data->tick);

    int player_number = data->tick++ % 2 + 1;

    select_stone_position(data, player_number);

    char player_glyph = (player_number == 1 ? data->p1id : data->p2id).player.glyph;
    if (check_winnmok(data->grd->grid, 5, data->grd->width, data->grd->height, data->grd->cursor_x, data->grd->cursor_y,
                      player_glyph))
    {
        add_game_message_with_draw(data->msg, player_glyph == SG_BLACK ? L"흑의 승리입니다." : L"백의 승리입니다.");
        add_game_message_with_draw(data->msg, L"<대국이 끝났습니다>");
        //get_key_input();
        //change_status(data, GS_MAIN);
    }
    //draw_player_interface(&data->p1id);
    //draw_player_interface(&data->p2id);
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
    set_encoding_cp949();
    set_locale_korean();
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