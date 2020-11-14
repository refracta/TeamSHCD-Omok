#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "inc/gamehandler.h"
#include "inc/consoleutils.h"
#include "inc/systemutils.h"
#include "inc/interfacerenderer.h"
#include "inc/environment.h"
#include "inc/gameutils.h"
#include "inc/gamecore.h"
#include "inc/gamerenderer.h"

/**
 * @brief ������ ������ ��Ȳ ������
 */
typedef enum
{
	GS_INTRO, GS_MAIN, GS_GAME, GS_HELP
} GameStatus;

/**
 * @brief ���ӿ��� ����ϴ� �����͵��� �����ϴ� ����ü
 */
typedef struct 
{
	GameStatus status;
	int tick;
} GameData;

/**
 * @brief ���� ������ ���¸� �����մϴ�. ���� �������� ���� ������ �����ϰ�, ���� ������� �ʱ�ȭ �۾��� �����Ѵ�.
 * @param data ���� ������ ����ü�� ������
 * @param data ���� ���� ������
 */
void change_status(GameData* data, GameStatus status) {
	data->status = status;
	data->tick = 0;
	set_print_color(TO_TBCOLOR(WHITE, BLACK));
	clear_console();
}

/**
 * @brief ��Ʈ�� ��ŵ�� Ű �ڵ鷯
 * @param c getch ��ȯ ��
 * @return Ű �ڵ鷯 ���
 */
int skip_intro(int c) {
	return 0;
}

/**
 * @brief ��Ʈ�� ���¿��� ����Ǵ� �Լ�
 * @param data ���� ������ ����ü�� ������
 */
void run_intro(GameData* data)
{
	draw_intro(data->tick++);
	if (wait_with_handler(20, skip_intro) > -1 || data->tick > INTRO_FULL_TICK) {
		change_status(data, GS_MAIN);
	}
}

/**
 * @brief ���� ȭ�� �޴� ������
 */
typedef enum
{
	MM_OMOK = 0, MM_NMOK, MM_HELP, MM_EXIT
} MainMenu;


/**
 * @brief ���� ȭ�� �޴��� �����Ѵ�.
 * @param ������ �޴� ����
 */
int run_main_menu() {
	MenuData menu;
	menu.name = " �޴�";
	char** list = malloc(sizeof(char*) * 4);
	list[0] = " ����";
	list[1] = " n��";
	list[2] = "����";
	list[3] = "������";
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
 * @brief ���� ���¿��� ����Ǵ� �Լ�
 * @param data ���� ������ ����ü�� ������
 */
void run_main(GameData* data)
{
	xyprintf(32, 6, "===================================================");
	xyprintf(32, 8, "            ���� ���α׷� - ������ (����)");
	xyprintf(32, 9, "���� �ڿ������� ��ų� ���̾� �𼭸��� ������� ��.");
	xyprintf(32, 11, "===================================================");
	int selection = run_main_menu();
	switch (selection) {
		case MM_OMOK:
			change_status(data, GS_GAME);
			break;
		case MM_NMOK:
			xyprintf(32, 12, "�������� �����Դϴ�.");
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
 * @brief ���� ���¿��� ����Ǵ� �Լ�
 * @param data ���� ������ ����ü�� ������
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
 * @brief ���� ���¿��� ����Ǵ� �Լ�
 * @param data ���� ������ ����ü�� ������
 */
void run_help(GameData* data)
{
	xyprintf(32, 12, "�����Դϴ�.");
}

/**
 * @brief ���� ������ ó���Ѵ�.
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
 * @brief ���� ���۽� �ʱ�ȭ �۾��� �����Ѵ�.
 */
void init_game() 
{
	set_cursor_visibility(false);
	set_console_size(CONSOLE_COLS, CONSOLE_LINES);
}

/**
 * @brief ������ �����Ѵ�.
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