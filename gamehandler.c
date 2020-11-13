#include <stdio.h>
#include <stdbool.h>

#include "inc/gamehandler.h"
#include "inc/consoleutils.h"
#include "inc/systemutils.h"

/**
 * @brief ������ ������ ��Ȳ ������
 */
typedef enum
{
	INTRO, MAIN, GAME
} GameStatus;

/**
 * @brief ���ӿ��� ����ϴ� �����͵��� �����ϴ� ����ü
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
 * @brief ���� ������ ó���ϴ� �Լ�
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
 * @brief ������ �����ϴ� �Լ��Դϴ�.
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