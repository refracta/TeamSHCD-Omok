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
	PlayerData player1_data;
	PlayerData player2_data;
	TimerData player1_timer;
	TimerData player2_timer;
	GridRenderData* grd;
	bool status_inited;
	int tick;
} GameData;

/**
 * @brief 현재 게임의 상태를 변경합니다. 게임 데이터의 상태 변수를 변경하고, 상태 변경시의 초기화 작업을 수행한다.
 * @param data 게임 데이터 구조체의 포인터
 * @param data 게임 상태 열거형
 */
void change_status(GameData* data, GameStatus status)
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
int skip_intro(int c) {
	return 0;
}

/**
 * @brief 인트로 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_intro(GameData* data)
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
int run_main_menu() {
	MenuData menu;
	menu.name = L" 메뉴";
	wchar_t** list = malloc(sizeof(wchar_t*) * 4);
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

void* run_player_name_prompt(PlayerData* player1, PlayerData* player2) {
	PromptData prompt;
	prompt.message = L"Player1의 이름을 입력하세요";
	prompt.x = 39;
	prompt.y = 20;
	prompt.rlen = 30;
	prompt.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
	prompt.text_tbcolor = TO_TBCOLOR(RED, BLACK);
	prompt.message_tbcolor = TO_TBCOLOR(RED, WHITE);
	wchar_t* player1_name = run_prompt(&prompt);
	wcscpy(player1->name, player1_name);
	free(player1_name);
	prompt.message = L"Player2의 이름을 입력하세요";
	prompt.text_tbcolor = TO_TBCOLOR(BLUE, BLACK);
	prompt.message_tbcolor = TO_TBCOLOR(BLUE, WHITE);
	wchar_t* player2_name = run_prompt(&prompt);
	wcscpy(player2->name, player2_name);
}

/**
 * @brief 메인 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_main(GameData* data)
{
	if (!data->status_inited)
	{
		set_console_size(CONSOLE_COLS, CONSOLE_LINES);
		data->status_inited = true;
	}
	xyprintf(30, 1, ASCII_OMOK);
	int selection = run_main_menu();
	switch (selection) {
	case MM_OMOK:
		change_status(data, GS_GAME);
		break;
	case MM_NMOK:
		xywprintf(32, 12, L"추후지원 예정입니다.");
		wait(1000);
		xywprintf(32, 12, L"                    ");
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
void run_game(GameData* data)
{
	if (!data->status_inited)
	{
		set_console_size(CONSOLE_COLS, (int)(CONSOLE_LINES * 1.5));
		run_player_name_prompt(&data->player1_data, &data->player2_data);
		clear_console();

		data->grd = malloc_grd(19, 19);
		(data->grd)->line_color = TO_TBCOLOR(BLACK, YELLOW);
		(data->grd)->black_color = TO_TBCOLOR(BLACK, YELLOW);
		(data->grd)->white_color = TO_TBCOLOR(WHITE, YELLOW);
		(data->grd)->cursor_color = TO_TBCOLOR(LIGHT_GREEN, YELLOW);
		(data->grd)->banned_color = TO_TBCOLOR(LIGHT_RED, YELLOW);
		(data->grd)->x = 10;
		(data->grd)->y = 10;
    
    data->player1_timer.x = 10;
    data->player1_timer.y = 7;
    data->player1_timer.width = 19;
    data->player1_timer.bar_tbcolor = TO_TBCOLOR(BLACK, WHITE);
    data->player1_timer.outline_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    data->player1_timer.left_seconds = 10;
    data->player1_timer.percent = 100; // Max_Seconds
    draw_timer(&data->player1_timer);
    data->player1_timer = data->player1_timer;

    data->player2_timer.x = 10;
    data->player2_timer.y = 7 + 19 + 3;
    data->player2_timer.width = 19;
    data->player2_timer.bar_tbcolor = TO_TBCOLOR(BLACK, GRAY);
    data->player2_timer.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    data->player2_timer.left_seconds = 10;
    data->player2_timer.percent = 100; // Max_Seconds
    draw_timer(&data->player2_timer);
    data->player2_timer.bar_tbcolor = TO_TBCOLOR(BLACK, WHITE);
    data->player2_timer.outline_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    data->player2_timer = data->player2_timer;
    
		data->status_inited = true;
	}

	// xywprintf(0, 1, L"Player1: %s (Black)", data->player1_data.name);
	// xywprintf(0, 2, L"Player2: %s (White)", data->player2_data.name);
	// xywprintf(0, 3, L"Turn: %d", data->tick);

	data->player1_data.player_num = 1;
	data->player1_data.x = 10;
	data->player1_data.y = 2;
	data->player1_data.width = 19;
	data->player1_data.win = 1;
	data->player1_data.lose = 0;
	data->player1_data.glyph = 'b';
	data->player1_data.glyph_tbcolor = TO_TBCOLOR(WHITE, BLACK);
	data->player1_data.outline_tbcolor = TO_TBCOLOR(WHITE, BLACK);
	data->player1_data.text_tbcolor = TO_TBCOLOR(WHITE, BLACK);
	data->player1_data.player_tbcolor = TO_TBCOLOR(LIGHT_JADE, BLACK);
	draw_player(&data->player1_data);

	data->player2_data.player_num = 2;
	data->player2_data.x = 10;
	data->player2_data.y = 2 + 7 + 19 + 4;
	data->player2_data.width = 19;
	data->player2_data.win = 0;
	data->player2_data.lose = 1;
	data->player2_data.glyph = 'b';
	data->player2_data.glyph_tbcolor = TO_TBCOLOR(WHITE, BLACK);
	data->player2_data.outline_tbcolor = TO_TBCOLOR(WHITE, BLACK);
	data->player2_data.text_tbcolor = TO_TBCOLOR(WHITE, BLACK);
	data->player2_data.player_tbcolor = TO_TBCOLOR(LIGHT_PURPLE, BLACK);
	draw_player(&data->player2_data);

	int player = (data->tick++ % 2 == 0);
	select_stone_position(data->grd, player ? SG_BLACK : SG_WHITE, player ? &data->player1_timer : &data->player2_timer);
}

/**
 * @brief 도움말 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_help(GameData* data)
{

}

/**
 * @brief 게임 루프를 처리한다.
 */
void game_loop(GameData* data)
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