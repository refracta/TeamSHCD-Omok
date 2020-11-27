/**
 @file gamecore.c
 @brief 게임 코어
*/
#include "gamecore.h"

/**
* @brief SG_EMPTY로 초기화한 격자를 생성한다.
* @param width 격자의 가로 길이
* @param width 격자의 세로 길이
* @return 격자 이중 포인터
*/
char **generate_grid(int width, int height)
{
    char **grid = (char **) malloc_double_pointer(sizeof(char), width, height);
    if (grid == NULL)
    {
        return NULL;
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            grid[x][y] = SG_EMPTY;
        }
    }
    return grid;
}

/**
 * @brief 격자의 복사본을 만든다.
 * @param grid 돌이 놓인 오목판
 * @param copygrid 격자의 카피본
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 */
void copy_grid(char **grid, char **copygrid, int width, int height)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            copygrid[i][j] = grid[i][j];
        }
    }
}

/**
 * @brief 3*3 조건에 통과되는지 확인한다.
 * @param grid 돌이 놓인 오목판
 * @param x 놓는 돌의 x좌표
 * @param y 놓는 돌의 y좌표
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 * @param glyph 현재 돌의 색
 * @return 정상적인 수면 ture 3*3이면 false
 */
bool check_double_three(char **grid, int width, int height, int x, int y, char glyph)
{
    // 가로
    int check__33 = 0;
    int countglyphone = 0;
    int countglyphtwo = 0;
    int countglyph = 1;
    int countemptyone = 1;
    int countemptytwo = 1;
    int countreverseglyph = 0;
    int emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (x - i == -1)
        {
            break;
        }
        if (grid[x - i][y] == glyph)
        {
            emptycheck = 0;
            countglyphone++;
        }

        if (grid[x - i][y] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x - i][y] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptyone++;
                break;
            }

            if (countemptyone == 1)
            {
                countemptyone--;
            }
            else
            {
                break;
            }
        }
    }

    countemptytwo = countemptyone;
    if (countemptyone == 1)
    { //빈공간을 만나지않은경우 없었음을기록
        countemptyone = 0;
    }
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (x + i == width)
        {
            break;
        }

        if (grid[x + i][y] == glyph)
        {
            emptycheck = 0;
            countglyphtwo++;
        }

        //상대돌을 만나면 탐색중지
        if (grid[x + i][y] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x + i][y] == SG_EMPTY)
        {
            //두번연속으로 빈공간만날시 blink카운트를 되돌림.
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptytwo++;
                break;
            }

            if (countemptytwo == 1)
            {
                countemptytwo--;
            }
            else
            {
                break; //빈공간을만났으나 빈공간을 두번만나면 끝임
            }
        }
    }
    countglyph += (countglyphone + countglyphtwo);

    if (countglyph == 3)
    {
        //돌갯수가 3이면 열린 3인지 파악.

        int left = (countglyphone + countemptyone);
        int right = (countglyphtwo + countemptytwo);

        //벽으로 막힌경우 - 열린3이 아님
        if (x - left != 0 && x + right != width - 1)
        {
            if (x - left - 1 < 0 || x + right + 1 > width - 1)
            {
                check__33++;
            }
            else if (grid[x - left - 1][y] != TO_REVERSE_SG(glyph) && grid[x + right + 1][y] != TO_REVERSE_SG(glyph))
            {
                check__33++;
            }
        }
    }


    countglyphone = 0;
    countglyphtwo = 0;
    countglyph = 1;
    countemptyone = 1;
    countemptytwo = 1;
    countreverseglyph = 0;
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (y - i == -1)
        {
            break;
        }

        if (grid[x][y - i] == glyph)
        {
            emptycheck = 0;
            countglyphone++;
        }

        if (grid[x][y - i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x][y - i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptyone++;
                break;
            }

            if (countemptyone == 1)
            {
                countemptyone--;
            }
            else
            {
                break;
            }
        }
    }

    countemptytwo = countemptyone;
    if (countemptyone == 1)
    { //빈공간을 만나지않은경우 없었음을기록
        countemptyone = 0;
    }
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (y + i == height)
        {
            break;
        }

        if (grid[x][y + i] == glyph)
        {
            emptycheck = 0;
            countglyphtwo++;
        }

        if (grid[x][y + i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x][y + i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptytwo++;
                break;
            }

            if (countemptytwo == 1)
            {
                countemptytwo--;
            }
            else
            {
                break;
            }
        }

    }

    countglyph += (countglyphone + countglyphtwo);

    if (countglyph == 3)
    {
        //돌갯수가 3이면 열린 3인지 파악.

        int up = (countglyphone + countemptyone);
        int down = (countglyphtwo + countemptytwo);

        //벽으로 막힌경우 - 열린3이 아님
        if (y - up != 0 && y + down != height - 1)
        {
            if (y - up - 1 < 0 || y + down + 1 > height - 1)
            {
                check__33++;
            }
            else if (grid[x][y - up - 1] != TO_REVERSE_SG(glyph) && grid[x][y + down + 1] != TO_REVERSE_SG(glyph))
            {
                check__33++;
            }
        }
    }

    countglyphone = 0;
    countglyphtwo = 0;
    countglyph = 1;
    countemptyone = 1;
    countemptytwo = 1;
    countreverseglyph = 0;
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (x - i == -1 || y - i == -1)
        {
            break;
        }

        if (grid[x - i][y - i] == glyph)
        {
            emptycheck = 0;
            countglyphone++;
        }

        if (grid[x - i][y - i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x - i][y - i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptyone++;
                break;
            }

            if (countemptyone == 1)
            {
                countemptyone--;
            }
            else
            {
                break;
            }
        }
    }


    countemptytwo = countemptyone;
    if (countemptyone == 1)
    { //빈공간을 만나지않은경우 없었음을기록
        countemptyone = 0;
    }
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (x + i == width || y + i == height)
        {
            break;
        }

        if (grid[x + i][y + i] == glyph)
        {
            emptycheck = 0;
            countglyphtwo++;
        }

        if (grid[x + i][y + i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x + i][y + i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck = 1;
            }
            else
            {
                countemptytwo++;
                break;
            }

            if (countemptytwo == 1)
            {
                countemptytwo--;
            }
            else
            {
                break;
            }
        }
    }

    countglyph += (countglyphone + countglyphtwo);
    if (countglyph == 3)
    {
        //돌갯수가 3이면 열린 3인지 파악.

        int leftup = (countglyphone + countemptyone);
        int rightDown = (countglyphtwo + countemptytwo);
        //벽으로 막힌경우 - 열린3이 아님
        if (x - leftup != 0 && y - leftup != 0 && x + rightDown != width - 1 && y + rightDown != height - 1)
        {
            if (x - leftup - 1 < 0 || y - leftup - 1 < 0 || x + rightDown + 1 > width - 1 ||
                y + rightDown + 1 > height - 1)
            {
                check__33++;
            }
            else if (grid[x - leftup - 1][y - leftup - 1] != TO_REVERSE_SG(glyph) &&
                     grid[x + rightDown + 1][y + rightDown + 1] != TO_REVERSE_SG(glyph))
            {
                check__33++;
            }
        }
    }

    countglyphone = 0;
    countglyphtwo = 0;
    countglyph = 1;
    countemptyone = 1;
    countemptytwo = 1;
    countreverseglyph = 0;
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (x - i == -1 || y + i == height)
        {
            break;
        }

        if (grid[x - i][y + i] == glyph)
        {
            emptycheck = 0;
            countglyphone++;
        }

        if (grid[x - i][y + i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x - i][y + i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptyone++;
                break;
            }

            if (countemptyone == 1)
            {
                countemptyone--;
            }
            else
            {
                break;
            }
        }
    }

    countemptytwo = countemptyone;
    if (countemptyone == 1)
    { //빈공간을 만나지않은경우 없었음을기록
        countemptyone = 0;
    }
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (x + i == width || y - i == -1)
        {
            break;
        }

        if (grid[x + i][y - i] == glyph)
        {
            emptycheck = 0;
            countglyphtwo++;
        }

        if (grid[x + i][y - i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x + i][y - i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptytwo++;
                break;
            }

            if (countemptytwo == 1)
            {
                countemptytwo--;
            }
            else
            {
                break;
            }
        }
    }

    countglyph += (countglyphone + countglyphtwo);
    if (countglyph == 3)
    {
        //돌갯수가 3이면 열린 3인지 파악.

        int leftDown = (countglyphone + countemptyone);
        int rightUp = (countglyphtwo + countemptytwo);

        //벽으로 막힌경우 - 열린3이 아님
        if (x - leftDown != 0 && y - rightUp != 0 && x + rightUp != width - 1 && y + leftDown != height - 1)
        {
            if (x - leftDown - 1 < 0 || y - rightUp - 1 < 0 || x + rightUp + 1 > width - 1 ||
                y + leftDown + 1 > height - 1)
            {
                check__33++;
            }
            else if (grid[x - leftDown - 1][y + leftDown + 1] != TO_REVERSE_SG(glyph) &&
                     grid[x + rightUp + 1][y - rightUp - 1] != TO_REVERSE_SG(glyph))
            {
                check__33++;
            }
        }
    }
    if (check__33 >= 2)
    {
        return false;
    }
    else
    {
        return true;
    }

}

/**
 * @brief 4*4 조건,장목,승리 조건 중 선택하여 통과되는지 확인한다.
 * @param grid 돌이 놓인 오목판
 * @param n N개를 둬야 승리하는지 알려준다.
 * @param x 놓는 돌의 x좌표
 * @param y 놓는 돌의 y좌표
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 * @param check_type 4*4,장목,오목 승리 판별을 선택하는데 이용한다.
 * @param glyph 현재 돌의 색
 * @return 정상적인 수거나 승리하였으면 ture 금수이거나 승리하지 않았으면 false
 */
bool check_all_conditions(char **grid, int n, int width, int height, int x, int y, char glyph, CheckType check_type)
{
    if (glyph == SG_WHITE)
    {
        return check_winnmok(grid, n, width, height, x, y, glyph);
    }
    int check__44 = 0;
    int countglyphone = 0;
    int countglyphtwo = 0;
    int countglyph = 1;
    int countemptyone = 1;
    int countemptytwo = 1;
    int countreverseglyph = 0;
    int emptycheck = 0;
    int overemptyone = 0;
    int overfourone = 0;
    int overemptytwo = 0;
    int overfourtwo = 0;
    int winx[20] = {0};
    int winy[20] = {0};
    int wincheck = 0;

    if (check_type == 2 || check_type == 3)
    {
        countemptyone = 0;
        countemptytwo = 0;
    }

    for (int i = 1;; i++)
    {
        if (x - i == -1)
        {
            break;
        }

        if (grid[x - i][y] == glyph)
        {
            emptycheck = 0;
            countglyphone++;
            winx[wincheck] = x - i;
            winy[wincheck] = y;
            wincheck++;
            if (i == 2 && overemptyone == 1)
            {
                overfourone++;
            }

        }

        if (grid[x - i][y] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x - i][y] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptyone++;
                break;
            }

            if (countemptyone == 1)
            {
                countemptyone--;
            }
            else
            {
                break;
            }

            if (i == 1)
            {
                overemptyone++;
            }
        }
    }

    countemptytwo = countemptyone;
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (x + i == width)
        {
            break;
        }

        if (grid[x + i][y] == glyph)
        {
            emptycheck = 0;
            countglyphtwo++;
            winx[wincheck] = x + i;
            winy[wincheck] = y;
            wincheck++;
            if (i == 2 && overemptytwo == 1)
            {
                overfourtwo++;
            }
        }

        if (grid[x + i][y] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x + i][y] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptytwo++;
                break;
            }

            if (countemptytwo == 1)
            {
                countemptytwo--;
            }
            else
            {
                break;
            }

            if (i == 1)
            {
                overemptytwo++;
            }
        }
    }

    countglyph += (countglyphone + countglyphtwo);

    if (check_type == 1)
    {
        if (countglyph == 4)
        {
            check__44++;
        }
        else if ((countglyphone == 3 && overfourtwo == 1) || (countglyphtwo == 3 && overfourone == 1))
        {
            check__44++;
        }
    }

    if (check_type == 2)
    {
        if (countglyph >= 6 && countglyphone != 0 && countglyphtwo != 0)
        {
            return false;
        }
    }

    if (check_type == 3)
    {
        if (countglyph == n)
        {
            //get_win_line(grid, n, winx, winy, width, height, glyph);
            return true;
        }
    }

    countglyphone = 0;
    countglyphtwo = 0;
    countglyph = 1;
    countemptyone = 1;
    countemptytwo = 1;
    countreverseglyph = 0;
    emptycheck = 0;
    overemptyone = 0;
    overfourone = 0;
    overemptytwo = 0;
    overfourtwo = 0;
    wincheck = 0;
    if (check_type == 2 || check_type == 3)
    {
        countemptyone = 0;
        countemptytwo = 0;
    }

    for (int i = 1;; i++)
    {
        if (y - i == -1)
        {
            break;
        }

        if (grid[x][y - i] == glyph)
        {
            emptycheck = 0;
            countglyphone++;
            winx[wincheck] = x;
            winy[wincheck] = y - i;
            wincheck++;
            if (i == 2 && overemptyone == 1)
            {
                overfourone++;
            }
        }

        if (grid[x][y - i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x][y - i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptyone++;
                break;
            }

            if (countemptyone == 1)
            {
                countemptyone--;
            }
            else
            {
                break;
            }

            if (i == 1)
            {
                overemptyone++;
            }
        }
    }

    countemptytwo = countemptyone;
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (y + i == height)
        {
            break;
        }

        if (grid[x][y + i] == glyph)
        {
            emptycheck = 0;
            countglyphtwo++;
            winx[wincheck] = x;
            winy[wincheck] = y + i;
            wincheck++;
            if (i == 2 && overemptytwo == 1)
            {
                overfourtwo++;
            }
        }

        if (grid[x][y + i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x][y + i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptytwo++;
                break;
            }

            if (countemptytwo == 1)
            {
                countemptytwo--;
            }
            else
            {
                break;
            }

            if (i == 1)
            {
                overemptytwo++;
            }
        }

    }

    countglyph += (countglyphone + countglyphtwo);

    if (check_type == 1)
    {
        if (countglyph == 4)
        {
            check__44++;
        }
        else if ((countglyphone == 3 && overfourtwo == 1) || (countglyphtwo == 3 && overfourone == 1))
        {
            check__44++;
        }
    }

    if (check_type == 2)
    {
        if (countglyph >= 6 && countglyphone != 0 && countglyphtwo != 0)
        {
            return false;
        }
    }

    if (check_type == 3)
    {
        if (countglyph == n)
        {
            //get_win_line(grid, n, winx, winy, width, height, glyph);
            return true;
        }
    }


    countglyphone = 0;
    countglyphtwo = 0;
    countglyph = 1;
    countemptyone = 1;
    countemptytwo = 1;
    countreverseglyph = 0;
    emptycheck = 0;
    overemptyone = 0;
    overfourone = 0;
    overemptytwo = 0;
    overfourtwo = 0;
    wincheck = 0;

    if (check_type == 2 || check_type == 3)
    {
        countemptyone = 0;
        countemptytwo = 0;
    }

    for (int i = 1;; i++)
    {
        if (x - i == -1 || y - i == -1)
        {
            break;
        }

        if (grid[x - i][y - i] == glyph)
        {
            emptycheck = 0;
            countglyphone++;
            winx[wincheck] = x - i;
            winy[wincheck] = y - i;
            wincheck++;
            if (i == 2 && overemptyone == 1)
            {
                overfourone++;
            }
        }

        if (grid[x - i][y - i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x - i][y - i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptyone++;
                break;
            }

            if (countemptyone == 1)
            {
                countemptyone--;
            }
            else
            {
                break;
            }

            if (i == 1)
            {
                overemptyone++;
            }
        }
    }


    countemptytwo = countemptyone;
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (x + i == width || y + i == height)
        {
            break;
        }

        if (grid[x + i][y + i] == glyph)
        {
            emptycheck = 0;
            countglyphtwo++;
            winx[wincheck] = x + i;
            winy[wincheck] = y + i;
            wincheck++;
            if (i == 2 && overemptytwo == 1)
            {
                overfourtwo++;
            }
        }

        if (grid[x + i][y + i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x + i][y + i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptytwo++;
                break;
            }

            if (countemptytwo == 1)
            {
                countemptytwo--;
            }
            else
            {
                break;
            }

            if (i == 1)
            {
                overemptytwo++;
            }
        }
    }

    countglyph += (countglyphone + countglyphtwo);

    if (check_type == 1)
    {
        if (countglyph == 4)
        {
            check__44++;
        }
        else if ((countglyphone == 3 && overfourtwo == 1) || (countglyphtwo == 3 && overfourone == 1))
        {
            check__44++;
        }
    }

    if (check_type == 2)
    {
        if (countglyph >= 6 && countglyphone != 0 && countglyphtwo != 0)
        {
            return false;
        }
    }

    if (check_type == 3)
    {
        if (countglyph == n)
        {
            //get_win_line(grid, n, winx, winy, width, height, glyph);
            return true;
        }
    }


    countglyphone = 0;
    countglyphtwo = 0;
    countglyph = 1;
    countemptyone = 1;
    countemptytwo = 1;
    countreverseglyph = 0;
    emptycheck = 0;
    overemptyone = 0;
    overfourone = 0;
    overemptytwo = 0;
    overfourtwo = 0;
    wincheck = 0;

    if (check_type == 2 || check_type == 3)
    {
        countemptyone = 0;
        countemptytwo = 0;
    }

    for (int i = 1;; i++)
    {
        if (x - i == -1 || y + i == height)
        {
            break;
        }

        if (grid[x - i][y + i] == glyph)
        {
            emptycheck = 0;
            countglyphone++;
            winx[wincheck] = x - i;
            winy[wincheck] = y + i;
            wincheck++;
            if (i == 2 && overemptyone == 1)
            {
                overfourone++;
            }
        }

        if (grid[x - i][y + i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x - i][y + i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptyone++;
                break;
            }

            if (countemptyone == 1)
            {
                countemptyone--;
            }
            else
            {
                break;
            }

            if (i == 1)
            {
                overemptyone++;
            }
        }
    }

    countemptytwo = countemptyone;
    emptycheck = 0;

    for (int i = 1;; i++)
    {
        if (x + i == width || y - i == -1)
        {
            break;
        }

        if (grid[x + i][y - i] == glyph)
        {
            emptycheck = 0;
            countglyphtwo++;
            winx[wincheck] = x + i;
            winy[wincheck] = y - i;
            wincheck++;
            if (i == 2 && overemptytwo == 1)
            {
                overfourtwo++;
            }
        }

        if (grid[x + i][y - i] == TO_REVERSE_SG(glyph))
        {
            break;
        }

        if (grid[x + i][y - i] == SG_EMPTY)
        {
            if (emptycheck == 0)
            {
                emptycheck++;
            }
            else
            {
                countemptytwo++;
                break;
            }

            if (countemptytwo == 1)
            {
                countemptytwo--;
            }
            else
            {
                break;
            }

            if (i == 1)
            {
                overemptytwo++;
            }
        }
    }

    countglyph += (countglyphone + countglyphtwo);

    if (check_type == 1)
    {
        if (countglyph == 4)
        {
            check__44++;
        }
        else if ((countglyphone == 3 && overfourtwo == 1) || (countglyphtwo == 3 && overfourone == 1))
        {
            check__44++;
        }
    }

    if (check_type == 2)
    {
        if (countglyph >= 6 && countglyphone != 0 && countglyphtwo != 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    if (check_type == 3)
    {
        if (countglyph == n)
        {
            //get_win_line(grid, n, winx, winy, width, height, glyph);
            return true;
        }
        else
        {
            return false;
        }
    }

    if (check_type == 1)
    {
        char **copygrid = generate_grid(width, height);
        copy_grid(grid, copygrid, width, height);

        copygrid[x][y] = glyph;

        // 추가 경우의 수
        // B B 빈칸 B B 빈칸 B B
        for (int j = 0; j < width - 7; j++) // 세로
        {
            if (copygrid[j][y] == glyph && copygrid[j + 1][y] == glyph && copygrid[j + 2][y] == SG_EMPTY &&
                copygrid[j + 3][y] == glyph && copygrid[j + 4][y] == glyph && copygrid[j + 5][y] == SG_EMPTY &&
                copygrid[j + 6][y] == glyph && copygrid[j + 7][y] == glyph &&
                ((j != 0 && copygrid[j - 1][y] != glyph) && (j != width - 8 && copygrid[j + 8][y] != glyph)))
            {
                free_double_pointer(copygrid, width);
                return false;
            }

        }

        for (int i = 0; i < height - 7; i++) // 가로
        {
            if (copygrid[x][i] == glyph && copygrid[x][i + 1] == glyph && copygrid[x][i + 2] == SG_EMPTY &&
                copygrid[x][i + 3] == glyph && copygrid[x][i + 4] == glyph && copygrid[x][i + 5] == SG_EMPTY &&
                copygrid[x][i + 6] == glyph && copygrid[x][i + 7] == glyph &&
                ((i != 0 && copygrid[x][i - 1] != glyph) && (i != height - 8 && copygrid[x][i + 8] != glyph)))
            {
                free_double_pointer(copygrid, width);
                return false;
            }

        }

        for (int j = 0; j < width - 7; j++) // 우측으로 떨어지는 대각선
        {
            for (int i = 0; i < height - 7; i++)
            {
                if (copygrid[j][i] == glyph && copygrid[j + 1][i + 1] == glyph && copygrid[j + 2][i + 2] == SG_EMPTY &&
                    copygrid[j + 3][i + 3] == glyph && copygrid[j + 4][i + 4] == glyph &&
                    copygrid[j + 5][i + 5] == SG_EMPTY && copygrid[j + 6][i + 6] == glyph &&
                    copygrid[j + 7][i + 7] == glyph && ((j != 0 && i != 0 && copygrid[j - 1][i - 1] != glyph) &&
                                                        (j != width - 8 && i != height - 8 &&
                                                         copygrid[j + 8][i + 8] != glyph)))
                {
                    free_double_pointer(copygrid, width);
                    return false;
                }

            }
        }
        for (int j = 0; j < width - 7; j++) // 좌측으로 떨어지는 대각선
        {
            for (int i = 7; i < height; i++)
            {
                if (copygrid[j][i] == glyph && copygrid[j + 1][i - 1] == glyph && copygrid[j + 2][i - 2] == SG_EMPTY &&
                    copygrid[j + 3][i - 3] == glyph && copygrid[j + 4][i - 4] == glyph &&
                    copygrid[j + 5][i - 5] == SG_EMPTY && copygrid[j + 6][i - 6] == glyph &&
                    copygrid[j + 7][i - 7] == glyph &&
                    ((j != 0 && i != height - 1 && copygrid[j - 1][i + 1] != glyph) &&
                     (j != width - 8 && i != 7 && copygrid[j + 8][i - 8] != glyph)))
                {
                    free_double_pointer(copygrid, width);
                    return false;
                }

            }
        }

        // B 빈칸 B B B 빈칸 B

        for (int j = 0; j < width - 6; j++) // 가로
        {
            if ((copygrid[j][y] == glyph && copygrid[j + 1][y] == SG_EMPTY && copygrid[j + 2][y] == glyph &&
                 copygrid[j + 3][y] == glyph && copygrid[j + 4][y] == glyph && copygrid[j + 5][y] == SG_EMPTY &&
                 copygrid[j + 6][y] == glyph) &&
                ((j != 0 && copygrid[j - 1][y] != glyph) && (j != width - 7 && copygrid[j + 7][y] != glyph)))
            {
                free_double_pointer(copygrid, width);
                return false;
            }

        }


        for (int i = 0; i < height - 6; i++) // 세로
        {
            if ((copygrid[x][i] == glyph && copygrid[x][i + 1] == SG_EMPTY && copygrid[x][i + 2] == glyph &&
                 copygrid[x][i + 3] == glyph && copygrid[x][i + 4] == glyph && copygrid[x][i + 5] == SG_EMPTY &&
                 copygrid[x][i + 6] == glyph) &&
                ((i != 0 && copygrid[x][i - 1] != glyph) && (i != height - 7 && copygrid[x][i + 7] != glyph)))
            {
                free_double_pointer(copygrid, width);
                return false;
            }

        }

        for (int j = 0; j < width - 6; j++) // 우측으로 떨어지는 대각선
        {
            for (int i = 0; i < height - 6; i++)
            {
                if (copygrid[j][i] == glyph && copygrid[j + 1][i + 1] == SG_EMPTY && copygrid[j + 2][i + 2] == glyph &&
                    copygrid[j + 3][i + 3] == glyph && copygrid[j + 4][i + 4] == glyph &&
                    copygrid[j + 5][i + 5] == SG_EMPTY && copygrid[j + 6][i + 6] == glyph &&
                    ((j != 0 && i != 0 && copygrid[j - 1][i - 1] != glyph) &&
                     (j != width - 7 && i != height - 7 && copygrid[j + 7][i + 7] != glyph)))
                {
                    free_double_pointer(copygrid, width);
                    return false;
                }

            }
        }
        for (int j = 0; j < width - 6; j++) // 좌측으로 떨어지는 대각선
        {
            for (int i = 6; i < height; i++)
            {
                if (copygrid[j][i] == glyph && copygrid[j + 1][i - 1] == SG_EMPTY && copygrid[j + 2][i - 2] == glyph &&
                    copygrid[j + 3][i - 3] == glyph && copygrid[j + 4][i - 4] == glyph &&
                    copygrid[j + 5][i - 5] == SG_EMPTY && copygrid[j + 6][i - 6] == glyph &&
                    ((j != 0 && i != height - 1 && copygrid[j - 1][i + 1] != glyph) &&
                     (j != width - 7 && i != 6 && copygrid[j + 7][i - 7] != glyph)))
                {
                    free_double_pointer(copygrid, width);
                    return false;
                }
            }
        }
        if (check__44 > 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

/**
 * @brief N개의 돌이 연속적으로 놓아져 승리했는지 확인한다.
 * @param N목에서 N의 수
 * @param x 놓는 돌의 x좌표
 * @param y 놓는 돌의 y좌표
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 * @glyph 현재 돌의 색깔
 * @return 승리했으면 true, 패배했으면 false
 */
bool check_winnmok(char **grid, int n, int width, int height, int x, int y, char glyph)
{
    int checkglyph = 0;
    for (int i = 0; i < width - (n - 1); i++)
    {
        for (int a = 0; a < n; a++)
        {
            if (grid[i + a][y] == glyph)
            {
                checkglyph++;
            }
            else
            {
                break;
            }
        }
        if (checkglyph == n)
        {
            return true;
        }
        checkglyph = 0;
    }

    for (int i = 0; i < height - (n - 1); i++)
    {
        for (int a = 0; a < n; a++)
        {
            if (grid[x][i + a] == glyph)
            {
                checkglyph++;
            }
            else
            {
                break;
            }
        }
        if (checkglyph == n)
        {
            return true;
        }
        checkglyph = 0;
    }

    for (int i = 0; i < width - (n - 1); i++)
    {
        for (int j = 0; j < height - (n - 1); j++)
        {
            for (int a = 0; a < n; a++)
            {
                if (grid[i + a][j + a] == glyph)
                {
                    checkglyph++;
                }
                else
                {
                    break;
                }
            }
            if (checkglyph == n)
            {
                return true;
            }
            checkglyph = 0;
        }
    }

    for (int i = 0; i < width - (n - 1); i++)
    {
        for (int j = (n - 1); j < height; j++)
        {
            for (int a = 0; a < n; a++)
            {
                if (grid[i + a][j - a] == glyph)
                {
                    checkglyph++;
                }
                else
                {
                    break;
                }
            }
            if (checkglyph == n)
            {
                return true;
            }
            checkglyph = 0;
        }
    }

    return false;
}

/**
 * @brief 렌주룰 조건을 모두 확인하여 승리하였는지, 둘 수 있는지, 금수인지 확인한다.
 * @param grid 돌이 놓인 오목판
 * @param x 놓는 돌의 x좌표
 * @param y 놓는 돌의 y좌표
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 * @param glyph 현재 돌의 색
 * @return 승리하거나 유효하면 PLACE_VALID, 3*3 조건에 부합하지 않으면 PLACE_33,
           4*4조건에 부합하지 않으면 PLACE_44, 장목 조건에 부합하지 않으면 PLACE_OVERLINE
 */
CheckResult check_confirm_omok(char **grid, int width, int height, int x, int y, char glyph)
{
    if (glyph == SG_BLACK)
    {

        if (check_all_conditions(grid, 5, width, height, x, y, glyph, 3))
        {
            return PLACE_VALID;
        }
        else if (check_double_three(grid, width, height, x, y, glyph) &&
                 check_all_conditions(grid, 5, width, height, x, y, glyph, 1) &&
                 check_all_conditions(grid, 5, width, height, x, y, glyph, 2))
        {
            return PLACE_VALID;
        }
        else if (!check_double_three(grid, width, height, x, y, glyph))
        {
            return PLACE_33;
        }
        else if (!check_all_conditions(grid, 5, width, height, x, y, glyph, 1))
        {
            return PLACE_44;
        }
        else if (!check_all_conditions(grid, 5, width, height, x, y, glyph, 2))
        {
            return PLACE_OVERLINE;
        }
    }
    else if (glyph == SG_WHITE)
    {
        return PLACE_VALID;
    }
}

/**
 * @brief N개의 돌이 연속적으로 놓아져 승리했는지 확인한다.
 * @param grid 격자 데이터
 * @param x 놓는 돌의 x좌표
 * @param y 놓는 돌의 y좌표
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 * @glyph 현재 돌의 색깔
 * @return 승리한 돌 라인 데이터 Example:  { {stone1_x, stone1_y}, {stone2_x, stone2_y}, {stone3_x, stone3_y}, ... }
 */
int **get_win_line(char **grid, int n, int width, int height, char glyph)
{
    int **win_line = (int **) malloc_double_pointer(sizeof(int), n, 2);
    // Test Case
    for (int i = 0; i < n; i++)
    {
        win_line[i][0] = glyph == SG_BLACK ? 10 : 11;
        win_line[i][1] = i;
    }
    return win_line;
}