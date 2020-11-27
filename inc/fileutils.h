#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "consoleutils.h"

typedef struct
{
    wchar_t name[BUFSIZ];
    int win;
    int rank;
} RankedPlayer;

int file_append(char path[], wchar_t data[]);

void append_rank(wchar_t winner_name[], wchar_t loser_name[]);

int get_exist(char path[], wchar_t name[]);

fpos_t *get_file_cur(char path[], int curIndex, fpos_t pos[]);

void print_ranking();

void ascending(RankedPlayer player[], int length);

#endif