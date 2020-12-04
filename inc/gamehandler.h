#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <locale.h>
#include <wchar.h>
#include "consoleutils.h"
#include "systemutils.h"
#include "environment.h"
#include "interfacerunner.h"
#include "interfacerenderer.h"
#include "gamecore.h"
#include "gridrenderer.h"
#include "gameviewrenderer.h"
#include "gameviewutils.h"
#include "gameviewrunner.h"
#include "gamedata.h"
#include "keycode.h"
#include "beeputils.h"
#include "rankingutils.h"

void start_game();

#endif