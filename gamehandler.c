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
	int tick;
} GameData;

/**
 * @brief 현재 게임의 상태를 변경합니다. 게임 데이터의 상태 변수를 변경하고, 상태 변경시의 초기화 작업을 수행한다.
 * @param data 게임 데이터 구조체의 포인터
 * @param data 게임 상태 열거형
 */
void change_status(GameData* data, GameStatus status) {
	data->status = status;
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
	if (wait_with_handler(20, skip_intro) > -1 || data->tick > INTRO_FULL_TICK) {
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
	list[1] = L" n목";
	list[2] = L"도움말";
	list[3] = L"나가기";
	menu.list = list;
	menu.length = 4;
	menu.current_index = 0;

	menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
	menu.name_tbcolor = TO_TBCOLOR(WHITE, GRAY);
	menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
	menu.selected_tbcolor = TO_TBCOLOR(JADE, LIGHT_RED);

	menu.x = 51;
	menu.y = 17;

	int index = run_menu(&menu, true);
	free(list);
	return index;
}

/**
 * @brief 메인 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_main(GameData* data)
{
	xyprintf(32, 6, "===================================================");
	xyprintf(32, 8, "            오목 프로그램 - 구른돌 (가제)");
	xyprintf(32, 9, "돌이 자연적으로 닳거나 깎이어 모서리가 무디어진 돌.");
	xyprintf(32, 11, "===================================================");
	int selection = run_main_menu();
	switch (selection) {
	case MM_OMOK:
		change_status(data, GS_GAME);
		break;
	case MM_NMOK:
		xyprintf(32, 12, "추후지원 예정입니다.");
		wait(1000);
		xyprintf(32, 12, "                    ");
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
	char** grid = generate_grid(19, 19);
	grid[1][2] = SG_BLACK;
	grid[1][3] = SG_WHITE;
	render_grid(grid, 19, 19);
	get_key_input();
	free_grid(grid, 19);
	clear_console();
}

/**
 * @brief 도움말 상태에서 실행되는 함수
 * @param data 게임 데이터 구조체의 포인터
 */
void run_help(GameData* data)
{
	xyprintf(32, 12, "도움말입니다.");
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
	// setlocale(LC_ALL, "ko-KR");
	set_encoding_utf8();
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