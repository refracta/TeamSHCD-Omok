#include <stdio.h>
#include <stdbool.h>

#include "inc/gamehandler.h"
#include "inc/consoleutils.h"
#include "inc/systemutils.h"

/**
 * @brief 게임이 가지는 상황 열거형
 */
typedef enum
{
	INTRO, MAIN, GAME
} GameStatus;

/**
 * @brief 게임에서 사용하는 데이터들을 포함하는 구조체
 */
struct GameData 
{
	GameStatus status;
};

void run_intro(struct GameData* data)
{
	set_cursor_visibility(false);

	set_print_color(WHITE, BLACK);
	printf("THIS IS INTRO");

	set_print_color(RED, WHITE);
	xyprint(5, 5, "ABCDE\nFGHIJ\nKLNMO\nPQRST\nUVWXY\nZ");
	
	wait(3000);
	set_print_color(WHITE, BLACK);
	clear_console();
	data->status = MAIN;
}

int keytest(int c) {
	xyprint(10, 10, "KeyCode: %d (%c)", c, c);
	return -1;
}

void run_main(struct GameData* data)
{
	printf("WELCOME TO MAIN!");
	wait_with_handler(5000, keytest);
}

void run_game(struct GameData* data)
{

}

/**
 * @brief 게임 루프를 처리하는 함수
 */
void game_loop(struct GameData* data) 
{
	switch (data->status)
	{
		case INTRO:
			run_intro(data);
			break;
		case MAIN:
			run_main(data);
			break;
		case GAME:
			run_game(data);
			break;
	}
}

/**
 * @brief 게임을 시작하는 함수입니다.
 */
void start_game() 
{
	struct GameData data;
	data.status = INTRO;
	while (true) 
	{
		game_loop(&data);
	}
}