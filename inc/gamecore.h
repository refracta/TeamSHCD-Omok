#ifndef GAMECORE_H
#define GAMECORE_H

#include <stdlib.h>
#include <stdbool.h>
#include "memoryutils.h"

#define SG_BLACK 'b'
#define SG_WHITE 'w'
#define SG_EMPTY '.'
#define SG_CURSOR 'c'
#define SG_BANNED 'n'

#define TO_REVERSE_SG(sg) (sg == SG_BLACK ? SG_WHITE : SG_BLACK)

typedef enum 
{
	PLACE_33,
	PLACE_44,
	PLACE_OVERLINE,
	PLACE_VALID
}CheckResult;

char **generate_grid(int width, int height);

void copy_grid(char **grid, char **copygrid, int width, int height);

bool check_double_three(char **grid, int width, int height, int x, int y, char glyph);

bool check_doublefour_overline_fivewin(char **grid, int width, int height, int x, int y, char glyph, int number);

int check_confirm(char **grid, int width, int height, int x, int y, char glyph);

bool check_winnmok(char **grid, int n, int width, int height, int x, int y, char glyph);

#endif