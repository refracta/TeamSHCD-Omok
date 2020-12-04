/**
  @file dumputils.c
  @brief 덤프 파일 생성
*/

#include "dumputils.h"

/**
 * @brief 덤프파일 생성
 * @param string 저장할 게임 플레이 데이터 문자열
*/
void make_dump(wchar_t* string, GameData* data)
{
    wchar_t file_name[BUFSIZ] = { '\0', };
    time_t now_time = time(NULL);
    struct tm* tm = (struct tm*)localtime(&now_time);

    swprintf(file_name, BUFSIZ, L"[%s]vs[%s]_%04d%02d%02d_%02d%02d%02d.txt", data->p1id.player.name, data->p2id.player.name, tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    FILE* stream = _wfopen(file_name, L"w");
    fwprintf(stream, L"%s\n\n", string);

    for (int i = 0; i < data->grd->height; i++)
    {
        for (int j = 0; j < data->grd->width; j++)
        {
            if (data->grd->grid[j][i] != SG_EMPTY)
            {
                if (data->grd->grid[j][i] == SG_BLACK) fwprintf(stream, L"●");
                else if (data->grd->grid[j][i] == SG_WHITE) fwprintf(stream, L"○");
                continue;
            }
            if (i == 0 && j == 0)                                               fwprintf(stream, L"┌");
            else if (i == 0 && j == data->grd->width - 1)                       fwprintf(stream, L"┐");
            else if (i == 0)                                                    fwprintf(stream, L"┬");
            else if (i != data->grd->height - 1 && j == 0)                      fwprintf(stream, L"├");
            else if (i != data->grd->height - 1 && j == data->grd->width - 1)   fwprintf(stream, L"┤");
            else if (i == data->grd->height - 1 && j == 0)                      fwprintf(stream, L"└");
            else if (i == data->grd->height - 1 && j == data->grd->width - 1)   fwprintf(stream, L"┘");
            else if (i == data->grd->height - 1)                                fwprintf(stream, L"┴");
            else                                                                fwprintf(stream, L"┼");
        }
        fwprintf(stream, L"\n");
    }

    fclose(stream);
}