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