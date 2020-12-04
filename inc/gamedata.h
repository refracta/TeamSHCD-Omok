/**
 @file gamedata.h
 @brief 게임에서 사용되는 구조체, 상수, 데이터, 유틸 매크로등이 정의된 헤더 파일
*/
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

#define HELP_TEXT ( \
L"<오목 = 렌주룰>\n" \
L"흑·백 중 가로, 세로, 대각선 중에서 5개의 같은 돌을 연달아 놓으면 승리한다.\n" \
L"흑만 3x3, 4x4, 장목이 금수가 되고, 백은 금수가 없다.\n" \
L"단, 금수인 자리임에도 5개의 같은 돌을 연달아 놓는 자리면 승리하게 된다. \n\n" \
L"3x3 : 3이 동시에 두 개가 발생하여 상대편이 한 쪽을 막아도 다른 쪽으로 열린 4를 만들게 되는 지점을 말한다.\n" \
L"4x4 : 열림과 닫힘에 상관 없이 한 쪽으로 5가 만들어지는 지점이 두개 이상이 발생하는 지점을 말한다.\n" \
L"장목 : 가로,세로,대각선 중에서  6개 이상의 같은 돌이 연달아 놓아지는 지점이다.\n\n" \
L"<N목 = 자유룰> \n" \
L"흑·백 중 가로,세로,대각선 중에서 N개의 같은 돌을 연달아 놓으면 승리한다.\n" \
L"N은 시작 전에 4~10의 수 중 선택한다.\n" \
L"흑·백 모두 금수는 없다." \
)

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
    bool nmok_mode;
    bool regame;
    bool status_inited;
    int tick;
    int turn;
    wchar_t *dump_string;
} GameData;

#endif