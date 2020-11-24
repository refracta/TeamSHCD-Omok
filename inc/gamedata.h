#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "interfacerenderer.h"
#include "gridrenderer.h"
#include "consoleutils.h"

#define GRID_SIZE 19
#define GAME_VIEW_COLS 98
#define GAME_VIEW_LINES 35

#define DEFAULT_TBCOLOR TO_TBCOLOR(WHITE, BLACK)
#define GRD_LINE_TBCOLOR TO_TBCOLOR(BLACK, YELLOW)
#define GRD_BLACK_TBCOLOR TO_TBCOLOR(BLACK, YELLOW)
#define GRD_WHITE_TBCOLOR TO_TBCOLOR(WHITE, YELLOW)
#define GRD_CURSOR_TBCOLOR TO_TBCOLOR(LIGHT_GREEN, YELLOW)
#define GRD_BANNED_TBCOLOR TO_TBCOLOR(LIGHT_RED, YELLOW)

#define P1_DEFAULT_TBCOLOR TO_TBCOLOR(LIGHT_JADE, BLACK)
#define P1_GLYPH_TBCOLOR TO_TBCOLOR(BLACK, YELLOW)

#define P2_DEFAULT_TBCOLOR TO_TBCOLOR(LIGHT_PURPLE, BLACK)
#define P2_GLYPH_TBCOLOR TO_TBCOLOR(WHITE, YELLOW)

#define PI_OUTLINE_TBCOLOR TO_TBCOLOR(WHITE, BLACK)
#define PI_TEXT_TBCOLOR TO_TBCOLOR(WHITE, BLACK)
#define PI_BAR_TBCOLOR TO_TBCOLOR(BLACK, WHITE)
#define PI_DISABLED_BAR_TBCOLOR TO_TBCOLOR(BLACK, GRAY)
#define PI_DISABLED_OUTLINE_TBCOLOR TO_TBCOLOR(GRAY, BLACK)

/**
 * @brief 게임이 가지는 상황 열거형
 */
typedef enum
{
    GS_INTRO, GS_MAIN, GS_GAME, GS_RANKING, GS_HELP
} GameStatus;

/**
 * @brief 게임이 가지는 상황 열거형
 */
typedef enum
{
    SEC_10, SEC_20, SEC_30, SEC_INFINITY
} TimerValue;

#define TO_TIME_STRING(tv)             \
    (                                  \
        tv == SEC_10 ? L"10초" :       \
        tv == SEC_20 ? L"20초" :       \
        tv == SEC_30 ? L"30초" :       \
        tv == SEC_INFINITY ? L"무한" : \
        NULL                           \
    )

#define TO_SECOND(tv)             \
    (                             \
        tv == SEC_10 ? 10 :       \
        tv == SEC_20 ? 20 :       \
        tv == SEC_30 ? 30 :       \
        tv == SEC_INFINITY ? -1 : \
        NULL                      \
    )

/**
 * @brief 게임에서 사용하는 데이터들을 포함하는 구조체
 */
typedef struct
{
    GameStatus status;
    int victory_condition;
    PlayerInterfaceData p1id;
    PlayerInterfaceData p2id;
    wchar_t msg[8][BUFSIZ];
    GridRenderData *grd;
    TimerValue timer_value;
    bool regame;
    bool status_inited;
    int tick;
    int turn;
} GameData;

#endif