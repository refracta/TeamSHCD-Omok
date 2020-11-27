/**
  @file gameviewrenderer.c
  @brief 게임 화면 렌더러
*/
#include "gameviewrenderer.h"

/**
 * @brief 게임 규칙 인터페이스를 그립니다.
 */
void draw_game_rule(int victory_condition, wchar_t *time_limit)
{
    MenuData menu;
    menu.name = L"       규칙        ";
    wchar_t **list = malloc(sizeof(wchar_t *) * 4);

    wchar_t win_condition_text[BUFSIZ];
    swprintf(win_condition_text, BUFSIZ, L"승리: %d개의 돌", victory_condition);
    list[0] = win_condition_text;

    if (victory_condition == 5)
    {
        list[1] = L"렌주룰: 흑의 3x3,";
        list[2] = L"4x4, 장목 금지";
    }
    else
    {
        list[1] = L"자유룰: 금지 조건이";
        list[2] = L"없습니다.";
    }

    wchar_t time_limit_text[BUFSIZ];
    swprintf(time_limit_text, BUFSIZ, L"시간 제한: %s", time_limit);
    list[3] = time_limit_text;
    menu.list = list;
    menu.length = 4;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);

    menu.x = 53;
    menu.y = 8;
    draw_menu(&menu);

    free(list);
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

    menu.element_tbcolor = TO_TBCOLOR(BLACK, YELLOW);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, BLACK);

    menu.x = 53;
    menu.y = 17;

    draw_menu(&menu);

    free_double_pointer(copy_list, 8);
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