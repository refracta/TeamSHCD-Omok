/**
 @file interfacerunner.h
 @brief interfacerunner의 헤더 파일
*/
#ifndef INTERFACERUNNER_H
#define INTERFACERUNNER_H

#include <stdbool.h>
#include <locale.h>
#include "consoleutils.h"
#include "systemutils.h"
#include "interfacerenderer.h"
#include "gridrenderer.h"
#include "keycode.h"
#include "gamecore.h"
#include "beeputils.h"

int run_menu(MenuData *, bool);

wchar_t *run_prompt(PromptData *);

#endif