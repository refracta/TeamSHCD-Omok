/**
 @file interfacerenderer.h
 @brief interfacerenderer의 헤더 파일
*/
#ifndef INTERFACERENDERER_H
#define INTERFACERENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <math.h>

#include "environment.h"
#include "consoleutils.h"
#include "gridrenderer.h"
#include "gamecore.h"
#include "asciiart.h"
#include "wcharutils.h"

#define INTRO_FULL_TICK 210
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/**
 * @brief 메뉴 렌더링 데이터들을 포함하는 구조체
 */
typedef struct
{
    int x;
    int y;
    wchar_t *name;
    wchar_t **list;
    int length;
    int current_index;
    short outline_tbcolor;
    short name_tbcolor;
    short element_tbcolor;
    short selected_tbcolor;
    short non_selected_tbcolor;
} MenuData;

/**
 * @brief 프롬프트 렌더링 데이터들을 포함하는 구조체
 */
typedef struct
{
    int x;
    int y;
    wchar_t *message;
    int rlen;
    short outline_tbcolor;
    short message_tbcolor;
    short text_tbcolor;
} PromptData;

/**
 * @brief 타이머 렌더링 데이터들을 포함하는 구조체
 */
typedef struct
{
    int percent;
    int left_seconds;
} TimerData;

/**
 * @brief 플레이어 데이터를 포함하는 구조체
 */
typedef struct
{
    int player_number;
    short color;
    wchar_t name[BUFSIZ];
    int win;
    int lose;
    char glyph;
} PlayerData;

/**
 * @brief 플레이어 인터페이스 렌더링 데이터를 포함하는 구조체
 */
typedef struct
{
    int x;
    int y;
    int width;
    short glyph_tbcolor;
    short outline_tbcolor;
    short text_tbcolor;
    short bar_tbcolor;
    int direction;
    PlayerData player;
    TimerData timer;
} PlayerInterfaceData;

void draw_intro(int tick);

void draw_menu(MenuData *data);

void draw_prompt(PromptData *data);

void draw_player_interface(PlayerInterfaceData *data);

#endif


