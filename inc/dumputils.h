/**
 @file dumputils.h
 @brief dumputils의 헤더 파일
*/

#ifndef DUMPUTILS_H
#define DUMPUTILS_H

#include <stdio.h>
#include "gamedata.h"
#include "gamecore.h"

void make_dump(wchar_t *string, GameData *data);

#endif