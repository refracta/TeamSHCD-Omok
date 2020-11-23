/**
  @file gameviewrenderer.c
  @brief 게임 화면 렌더러
*/
#include "gameviewrenderer.h"

/**
 * @brief 게임 규칙 인터페이스를 그립니다.
 */
void draw_game_rule()
{

    MenuData menu;
    menu.name = L"       규칙";
    wchar_t **list = malloc(sizeof(wchar_t *) * 7);
    list[0] = L"승리 조건: 5개의 돌";
    list[1] = L"장목: 금지";
    list[2] = L"흑의 3x3: 금지";
    list[3] = L"시간 제한 20초";
    list[4] = L"";
    list[5] = L"착수 금지: 표시함";
    list[6] = L"오목판: 19x19";
    menu.list = list;
    menu.length = 7;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);

    menu.x = 39 + 14;
    menu.y = 5 + 3;
    draw_menu(&menu);

    //int index = run_menu(&menu, true);
    free(list);
    //return index;
}

/**
 * @brief 게임 메시지 인터페이스를 그립니다.
 * @param list 메시지 리스트
 */
void draw_game_message(wchar_t list[8][BUFSIZ])
{
    MenuData menu;
    menu.name = L"       메시지      ";
    wchar_t **copy_list = (wchar_t **) malloc_double_pointer(sizeof(wchar_t), 8, BUFSIZ);
    for (int i = 0; i < 8; i++)
    {
        wcscpy(copy_list[i], list[i]);
    }
    menu.list = copy_list;
    menu.length = 8;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);

    menu.x = 39 + 14;
    menu.y = 17;

    draw_menu(&menu);

//    int index = run_menu(&menu, true);
    free_double_pointer(copy_list, 8);
    //   return index;
}

/**
 * @brief 선택한
 * @param grd 격자 렌더 데이터
 */
void draw_select_stone(GridRenderData *grd)
{
    draw_grid(grd);
    if (grd->grid[grd->cursor_x][grd->cursor_y] != SG_EMPTY)
    {
        coloring_stone(grd->x, grd->y, grd->cursor_x, grd->cursor_y, SG_BANNED, grd->banned_color);
    }
    else
    {
        coloring_stone(grd->x, grd->y, grd->cursor_x, grd->cursor_y, SG_CURSOR, grd->cursor_color);
    }
}