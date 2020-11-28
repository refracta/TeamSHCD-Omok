/**
  @file fileutils.c
  @brief 파일 유틸
*/
#include "fileutils.h"

/**
 * @brief 파일에 값을 추가한다
 * @param path 파일의 경로
 * @param data 추가할 문자열
 * @return 오류가 있다면 -1, 정상 실행시 0
*/
int file_append(char path[], wchar_t data[])
{
    if (get_exist(path, data) == -1)
    {
        FILE *stream = fopen(path, "a");
        if (stream == NULL)
        {
            return -1;
        }
        fwprintf(stream, L"%s %04d\n", data, 1);
        fclose(stream);
    }
    else
    {
        FILE *stream = fopen(path, "r+");
        if (stream == NULL)
        {
            return -1;
        }
        int temp_count = 0;

        fpos_t pos[2] = {0};
        get_file_cur(path, get_exist(path, data), pos);
        fpos_t point = pos[0] - 6;
        fpos_t prev_line_pos = pos[1];

        fsetpos(stream, &point);

        fscanf(stream, "%d", &temp_count);
        temp_count++;
        fsetpos(stream, &prev_line_pos);
        fwprintf(stream, L"%s %04d\n", data, temp_count);

        fclose(stream);
    }

    return 0;
}

/**
 * @brief 플레이어의 승패를 파일로 저장한다
 * @param path 파일의 경로
 * @param winner_name 승리한 플레이어의 이름
 * @param loser_name 패배한 플레이어의 이름
*/
void append_rank(wchar_t winner_name[], wchar_t loser_name[])
{
    file_append("winData.omok", winner_name);
    //lose Data 필요시 주석 해제
    //file_append("loseData.omok", loser_name);
}

/**
 * @brief 이름을 입력받아 해당 이름이 존재하는지 판단한다
 * @param path 파일의 경로
 * @param name 검사할 이름
 * @return 이름이 파일에 존재하면 존재하는 줄 번호를 반환
*/
int get_exist(char path[], wchar_t name[])
{
    FILE *stream = fopen(path, "rt");

    if (stream == NULL)
    {
        return -1;
    }

    wchar_t compare_name[BUFSIZ];
    wchar_t buf[BUFSIZ];
    wchar_t *tempbuf;

    wcscpy(compare_name, name);
    wcscat(compare_name, L"\n");

    int index = 0;

    while (fgetws(buf, BUFSIZ, stream) != NULL)
    {
        tempbuf = wcstok(buf, L" ", NULL);
        wcscat(tempbuf, L"\n");
        if (wcscmp(tempbuf, compare_name) == 0)
        {
            return index;
        }
        index++;
    }
    return -1;
}

/**
 * @brief 현재 커서의 이전 행에서 파일 커서의 좌표를 가져온다.
 * @param path 파일의 경로
 * @param curindex 현재 커서 위치
 * @param pos[] 파일 커서의 좌표 ([0]: 현재 좌표, [1] 이전 좌표)가 담길 배열
 * @return 일치하는 행이 없을 경우 -1을 return하며, 그렇지 않은 경우 param3을 반환한다.
*/
fpos_t *get_file_cur(char path[], int curIndex, fpos_t pos[])
{
    FILE *stream = fopen(path, "rt");
    wchar_t buf[BUFSIZ];
    int index = 0;
    while (fgetws(buf, BUFSIZ, stream) != NULL)
    {
        if (index == curIndex)
        {
            fgetpos(stream, &pos[0]);
            return pos;
        }
        fgetpos(stream, &pos[1]);
        index++;
    }
    return -1;
}

/**
 * @brief 랭킹 출력
*/
void print_ranking()
{
    RankedPlayer player[BUFSIZ] = {-1};
    FILE *stream = fopen("winData.omok", "r+");
    wchar_t *tempbuf;

    if (stream == NULL)
    {
        xywprintf(50, 10, L"아직 랭킹이 없습니다!");
        return;
    }

    wchar_t buf[BUFSIZ];
    int index = 0;
    while (!feof(stream))
    {
        fwscanf(stream, L"%s %04d", player[index].name, &player[index].win);
        index++;
    }
    index--;
    fclose(stream);

    for (int i = 0; i < index; i++)
    {
        player[i].rank = 1;
        for (int j = 0; j < index; j++)
        {
            if (player[i].win < player[j].win)
            {
                player[i].rank++;
            }
        }
    }

    ascending(player, index);
    set_print_color(TO_TBCOLOR(BLACK, LIGHT_YELLOW));
    xywprintf(52, 4, L" 명 예 의   전 당 ");
    set_print_color(TO_TBCOLOR(WHITE, BLACK));
    xywprintf(43, 6, L"순위");
    xywprintf(43, 6, L"순위");
    xywprintf(49, 6, L"닉네임");
    xywprintf(75, 6, L"승리");
    if (index > 9)
    {
        index = 9;
    }
    short origin_color = get_print_color();
    for (int i = 0; i < index; i++)
    {
        if (player[i].rank <= 3)
        {
            set_print_color(14);
        }
        else
        {
            set_print_color(origin_color);
        }
        xywprintf(43, 9 + i * 2, L"%2d위: ", player[i].rank);
        xywprintf(49, 9 + i * 2, player[i].name);
        xywprintf(75, 9 + i * 2, L"%d회", player[i].win);
    }
}

/**
 * @brief 오름차순 정렬
 * @param player[] 랭킹순으로 정렬할 구조체
 * @param length 정렬할 요소의 개수
*/
void ascending(RankedPlayer player[], int length)
{
    int tmp = 0;
    wchar_t tmpstr[BUFSIZ] = {0};
    for (int i = 0; i < length; i++)
    {
        for (int j = i; j < length; j++)
        {
            if (player[i].rank > player[j].rank)
            {
                tmp = player[i].rank;
                player[i].rank = player[j].rank;
                player[j].rank = tmp;

                tmp = player[i].win;
                player[i].win = player[j].win;
                player[j].win = tmp;

                wcscpy(tmpstr, player[i].name);
                wcscpy(player[i].name, player[j].name);
                wcscpy(player[j].name, tmpstr);
            }
        }
    }
}

/**
 * @brief 덤프파일 생성
 * @param string 저장할 게임 플레이 데이터 문자열
*/
void make_dump(wchar_t *string)
{
    
    wchar_t file_name[BUFSIZ] = { '\0', };
    time_t now_time = time(NULL);
    struct tm *tm = (struct tm*)localtime(&now_time);

    swprintf(file_name, BUFSIZ, L"omok-%04d-%02d-%02d-%02d-%02d-%02d.txt", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    FILE *stream = _wfopen(file_name, L"w");
    fwprintf(stream, L"%s", string);
    fclose(stream);
    
}