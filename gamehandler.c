#include "inc/gamehandler.h"
#include "inc/consoleutils.h"

/**
 * @brief ������ ������ ��Ȳ ������
 */
enum GameStatus 
{
	INTRO, MAIN, GAME
};

/**
 * @brief ���ӿ��� ����ϴ� �����͵��� �����ϴ� ����ü
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
 * @brief ���� ������ ó���ϴ� �Լ�
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