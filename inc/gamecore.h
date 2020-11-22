#ifndef __GAMECORE_H__
#define __GAMECORE_H__

typedef enum
{
    BLACK_WIN, WHITE_WIN, DRAW, UNKNOWN
} GameResult;

typedef enum
{
    SG_BLACK = 'b', SG_WHITE = 'w', SG_EMPTY = '.', SG_CURSOR = 'c', SG_BANNED = 'n'
} StoneGlyph;
#endif

void **malloc_double_pointer(int, int, int);

void free_double_pointer(void **, int);

char **generate_grid(int, int);