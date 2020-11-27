#ifndef FILEUTILS_H
#define FILEUTILS_H

typedef struct
{
    wchar_t name[BUFSIZ];
    int win;
    int rank;
} rankedPlayer;

int file_append(char path[], wchar_t data[]);

void append_rank(wchar_t winner_name[], wchar_t loser_name[]);

int get_exist(char path[], wchar_t name[]);

fpos_t *get_file_cur(char path[], int curIndex, fpos_t pos[]);

void print_ranking();

void ascending(rankedPlayer player[]);

#endif