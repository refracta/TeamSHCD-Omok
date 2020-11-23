#ifndef GAMEVIEWRUNNER_H
#define GAMEVIEWRUNNER_H

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "consoleutils.h"
#include "gameviewrenderer.h"
#include "interfacerunner.h"
#include "gameviewutils.h"
#include "gamedata.h"
#include "keycode.h"

/**
 * @brief 메인 화면 메뉴 열거형
 */
typedef enum
{
    MM_OMOK, MM_NMOK, MM_HELP, MM_EXIT
} MainMenu;

int handle_ssp_key_input(int c, void *param);

void run_select_stone_position(GameData *data, int player_number);

void run_player_name_prompt(PlayerData *player1, PlayerData *player2);

int run_main_menu();
#endif