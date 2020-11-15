#ifndef __INTERFACERENDERER_H__
#define __INTERFACERENDERER_H__
typedef struct {
	wchar_t* name;
	wchar_t** list;
	int length;
	int current_index;
	int x;
	int y;
	short outline_tbcolor;
	short name_tbcolor;
	short element_tbcolor;
	short selected_tbcolor;
} MenuData;
#endif

#define ASCII_TITLE_SCHD (\
" .d8888b.   .d8888b.  888    888 8888888b. \n" \
"d88P  Y88b d88P  Y88b 888    888 888  \"Y88b\n" \
"Y88b.      888    888 888    888 888    888\n" \
" \"Y888b.   888        8888888888 888    888\n" \
"    \"Y88b. 888        888    888 888    888\n" \
"      \"888 888    888 888    888 888    888\n" \
"Y88b  d88P Y88b  d88P 888    888 888  .d88P\n" \
" \"Y8888P\"   \"Y8888P\"  888    888 8888888P\" ")

#define ASCII_SHC (\
"   ---------------------------. \n" \
" `/\"\"\"\"/\"\"\"\"/|\"\"|'|\"\"||\"\"|   ' \\. \n" \
" /    /    / |__| |__||__|      | \n" \
"/----------=====================| \n" \
"| \\  /V\\  /    _.  |      |     | \n" \
"|()\\ \\W/ /()   _   |      | _   | \n" \
"|   \\   /     / \\  |      |/ \\  |-( ) \n" \
"=C========C==_| ) |--------| ) _/==] _-{_}_) \n" \
" \\_\\_/__..  \\_\\_/_ \\_\\_/ \\_\\_/__.__. ")

#define ASCII_PEOPLE1 (\
"  .:.\n" \
" :-_-;\n" \
" ,`-'.\n" \
";, C \\\\\n" \
" |___|\n" \
" |_|_|\n" \
" `-'-'")

#define ASCII_PEOPLE2 (\
"  ,;;;,\n" \
" (-_- ;\n" \
"  >..'.\n" \
" /.   .| \n" \
"//| 2 ||\n" \
"' |___|)\n" \
"  | | |\n" \
"  |_|_|\n" \
"  `-'-'")

#define ASCII_DRUM_CAN (\
"|| | ||\n" \
"|| | ||\n" \
"|\\ | /|\n" \
"└-----┘")

#define ASCII_SMOKE1 (\
" \\ \\  \n" \
"  \\ \\ \n" \
"\\ \\  ")

#define ASCII_SMOKE2 (\
"   / /\n" \
" / / \n" \
"  / /")

#define ASCII_OMOK (\
"                                      _oooo.\n" \
"                                ,.,o8888P88b\n" \
"                               ,888PP'   d8b__\n" \
"           ,ooo.                88[ _oood88888\n" \
"          d8PPY88.              88d888PP\"'''             __\n" \
"         ]88   ]88              YPP';88            _,oo8888\n" \
"         ]88   d8P                  ]88       _ooo888PP\"''\n" \
"          Y88888P                   ]88__ooo8888P\"''\n" \
"           ']88                 __ood88888PP'''\n" \
"            ]88          __,ood8888PP'''_oo8b\n" \
"            ]88      ,oo8888PP\"''  oood888Y88\n" \
"            ]88_ooo888PP''        `PPPP'' ]88\n" \
"       ,ooooo8888P\"''                     ]88\n" \
"   dod888PPP\"''                           ]88\n" \
"  888P'''                                  88'\n" \
"  `'                                        '\"" )

#define INTRO_FULL_TICK 210
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define RG_MENU_TYPE_1 "┌"
#define RG_MENU_TYPE_2 "┬"
#define RG_MENU_TYPE_3 "┐"
#define RG_MENU_TYPE_4 "├"
#define RG_MENU_TYPE_5 "┼"
#define RG_MENU_TYPE_6 "┤"
#define RG_MENU_TYPE_7 "└"
#define RG_MENU_TYPE_8 "┴"
#define RG_MENU_TYPE_9 "┘"
#define RG_MENU_TYPE_H "─"
#define RG_MENU_TYPE_V = "│"

void draw_intro(int tick);
void draw_menu(MenuData* data);