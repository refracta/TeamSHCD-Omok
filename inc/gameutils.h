#include <stdbool.h>
#include "inc/interfacerenderer.h"
#include "inc/gamerenderer.h"

void select_stone_position(GridRenderData *, char, PlayerInterfaceData *);
int run_menu(MenuData*, bool);
wchar_t* run_prompt(PromptData* );