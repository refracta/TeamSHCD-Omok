#ifndef __GAMECORE_H__
#define __GAMECORE_H__

typedef enum
{
	BLACK_WIN, WHITE_WIN, DRAW, UNKNOWN
} GameResult;

typedef enum
{
	SG_BLACK = 'b', SG_WHITE = 'w', SG_EMPTY= '.'
} StoneGlyph;
#endif

char** malloc_grid(int width, int height);
void free_grid(char** grid, int width);
char** generate_grid(int width, int height);