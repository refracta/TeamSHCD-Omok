#ifndef GAMECORE_H
#define GAMECORE_H

#include <stdlib.h>
#include <stdbool.h>
#include "memoryutils.h"

#define TO_REVERSE_SG(sg) (sg == SG_BLACK ? SG_WHITE : SG_BLACK)

typedef enum
{
    BLACK_WIN, WHITE_WIN, DRAW, UNKNOWN
} GameResult;

typedef enum
{
    SG_BLACK = 'b', SG_WHITE = 'w', SG_EMPTY = '.', SG_CURSOR = 'c', SG_BANNED = 'n'
} StoneGlyph;

char **generate_grid(int width, int height);

void copy_grid(char **grid, char **copygrid, int width, int height);

bool check_double_three(char **grid, int width, int height, int x, int y, char glyph);

bool check_double_four(char **grid, int width, int height, int x, int y, char glyph);

bool check_overline(char **grid, int width, int height, int x, int y, char glyph);

bool check_confirm(char **grid, int width, int height, int x, int y, char glyph);

bool check_winnmok(char **grid, int n, int width, int height, int x, int y, char glyph);

#endif