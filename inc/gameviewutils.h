/**
 @file gameviewutils.h
 @brief gameviewutils의 헤더 파일
*/
#ifndef GAMEVIEWUTILS_H
#define GAMEVIEWUTILS_H

#include <stdio.h>
#include <wchar.h>
#include "interfacerenderer.h"
#include "consoleutils.h"
#include "gamedata.h"

void init_grd(GameData *data);

void init_pid(GameData *data);

int add_message_to_list(wchar_t list[8][BUFSIZ], wchar_t *data);

void set_player_interface_to_disable_color(PlayerInterfaceData *copy_id);

#endif