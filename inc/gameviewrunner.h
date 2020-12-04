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
#include "rankingutils.h"

/**
 * @brief 메인 화면 메뉴 열거형
 */
typedef enum
{
    MM_OMOK, MM_NMOK, MM_RANKING, MM_HELP, MM_EXIT
} MainMenu;

int handle_ssp_key_input(int c, void *param);

void run_select_stone_position(GameData *data, int player_number);

void run_player_name_prompt(PlayerData *player1, PlayerData *player2);

TimerValue run_select_timer_time_menu();

MainMenu run_main_menu();

int run_select_nmok_menu();

void run_win_line_blink(GridRenderData *grd, int victory_condition, char player_glyph, short blink_color, int number,
                        int wait_time);

void update_position_message(int turn, int x, int y, int player_number);
#endif