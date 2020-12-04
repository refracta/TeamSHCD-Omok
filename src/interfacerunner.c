/**
  @file interfacerunner.c
  @brief 인터페이스 실행
*/
#include "interfacerunner.h"

/**
* @brief 메뉴를 실행한다.
* @param data 메뉴 데이터
* @param disable_escape ESC 메뉴 종료 비활성화 여부
* @return 메뉴 항목 색인
*/
int run_menu(MenuData *data, bool disable_escape)
{
    int return_value = -1;
    draw_menu(data);
    while (true)
    {
        int c = get_key_input();
        switch (c)
        {
            case ESCAPE_KEY:
                if (!disable_escape)
                {
                    return -1;
                }
                break;
            case DOWN_KEY:
                data->current_index = data->current_index + 1 < data->length ? data->current_index + 1 : 0;
                draw_menu(data);
                FA(OCTAVE_5, 100);
                break;
            case UP_KEY:
                data->current_index = data->current_index > 0 ? data->current_index - 1 : data->length - 1;
                draw_menu(data);
                FA(OCTAVE_5, 100);
                break;
            case SPACE_KEY:
            case ENTER_KEY:
                SI(OCTAVE_5, 100);
                SOL(OCTAVE_5, 100);
                return data->current_index;
                break;
        }
    }
}

/**
* @brief 프롬프트를 실행한다.
* @param data 프롬프트 데이터
* @return 프롬프트 입력 텍스트
*/
wchar_t *run_prompt(PromptData *data)
{
    bool visibility = get_cursor_visibility();
    short color = get_print_color();
    set_cursor_visibility(true);

    draw_prompt(data);
    set_print_color(data->text_tbcolor);
    set_cursor_position(data->x + 4, data->y + 1);

    int index = 0;
    int crlen = 0;
    wchar_t *text = malloc(sizeof(wchar_t) * data->rlen + 2);
    if (text == NULL)
    {
        return NULL;
    }

    while (true)
    {
        int c = get_key_input();
        int crl;
        switch (c)
        {
            default:
                crl = is_full_width(c) ? 2 : 1;
                if (crlen + crl > data->rlen)
                {
                    continue;
                }
                if (crl == 1 && strchr("\\/:*?\"<>| ", (char)c)) //파일명에 사용할 수 없는 문자는 애초에 플레이어 이름으로 쓸 수 없게 한다.
                    continue;
                text[index++] = c;
                crlen += crl;
                wprintf(L"%c", c);
                break;
            case BACKSPACE_KEY:
                if (index <= 0)
                {
                    continue;
                }
                set_print_color(data->outline_tbcolor);
                if (is_full_width(text[index - 1]))
                {
                    crlen -= 2;
                    wprintf(L"%c%c", BACKSPACE_KEY, BACKSPACE_KEY);
                    wprintf(L"  ");
                    wprintf(L"%c%c", BACKSPACE_KEY, BACKSPACE_KEY);
                }
                else
                {
                    crlen--;
                    wprintf(L"%c", BACKSPACE_KEY);
                    wprintf(L" ");
                    wprintf(L"%c", BACKSPACE_KEY);
                }
                set_print_color(data->text_tbcolor);
                index--;
                break;
            case ENTER_KEY:
                if (index <= 0)
                {
                    continue;
                }
                text[index] = '\0';
                set_print_color(color);
                set_cursor_visibility(visibility);
                return text;
        }
    }
}
