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

int run_menu(MenuData *, bool);

wchar_t *run_prompt(PromptData *);

#endif