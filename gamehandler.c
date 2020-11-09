#include "inc/gamehandler.h"
#include "inc/consoleutils.h"

/**
 * @brief 게임이 가지는 상황 열거형
 */
enum GameStatus 
{
	INTRO, MAIN, GAME
};

/**
 * @brief 게임에서 사용하는 데이터들을 포함하는 구조체
 */
struct GameData 
{
	int status;
};

void run_intro() 
{

}

void run_main() 
{

}

void run_game() 
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
			run_intro();
			break;
		case MAIN:
			run_main();
			break;
		case GAME:
			run_game();
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