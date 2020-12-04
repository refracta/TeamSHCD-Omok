/**
 @file gamecore.h
 @brief gamecore의 헤더 파일
*/
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
} CheckResult;

typedef enum
{
    CHECK_44 = 1,
    CHECK_OVERLINE = 2,
    CHECK_WIN = 3
} CheckType;

char **generate_grid(int width, int height);

void copy_grid(char **grid, char **copygrid, int width, int height);

void send_location(int *inx, int *iny, int n, int number);

bool check_double_three(char **grid, int width, int height, int x, int y, char glyph);

bool check_all_conditions(char **grid, int n, int width, int height, int x, int y, char glyph, CheckType check_type);

CheckResult check_confirm_omok(char **grid, int width, int height, int x, int y, char glyph);

bool check_winnmok(char **grid, int n, int width, int height, int x, int y, char glyph);

int **get_win_line(char **grid, int n, int width, int height, char glyph);

#endif