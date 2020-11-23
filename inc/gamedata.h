#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "interfacerenderer.h"
#include "gridrenderer.h"

/**
 * @brief 게임이 가지는 상황 열거형
 */
typedef enum
{
    GS_INTRO, GS_MAIN, GS_GAME, GS_HELP
} GameStatus;

/**
 * @brief 게임에서 사용하는 데이터들을 포함하는 구조체
 */
typedef struct
{
    GameStatus status;
    PlayerInterfaceData p1id;
    PlayerInterfaceData p2id;
    wchar_t msg[8][BUFSIZ];
    GridRenderData *grd;
    bool status_inited;
    int tick;
} GameData;

#endif