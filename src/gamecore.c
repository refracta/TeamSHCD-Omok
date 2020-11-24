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
 * @param x 놓는 돌의 x좌표
 * @param y 놓는 돌의 y좌표
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 * @return 정상적인 수면 ture 3*3이면 false
 */
bool check_double_three(char **grid, int width, int height, int x, int y, char glyph)
{

    // 가로
    int countglyph = 1; // 두는 곳은 흑색이므로 1 추가
    int countempty = 0;
    int countreverseglyph = 0;
    int check__33 = 0;
    int opencheck = 0;
    // 가로 우측 방향 체크

    for (int i = 1; i < 4; i++)
    {
        if (x + i > width - 1)
        {
            break;
        }

        if (grid[x + i][y] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x + i][y] != TO_REVERSE_SG(glyph))
        {
            if (grid[x + i][y] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
                if (grid[x + i - 1][y] == SG_EMPTY && i > 1)
                    break;
            }
        }
        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && x + i + 1 < width)
        {
            if (grid[x + i + 1][y] == TO_REVERSE_SG(glyph))
            {
                countreverseglyph++;
            }
        }
    }

    // 한쪽이 열린 3인지 체킹
    if (countempty > countreverseglyph)
    {
        opencheck += 1;
    }

    // 가로 좌측 방향 체크
    for (int i = 1; i < 4; i++)
    {
        if (x - i < 0)
        {
            break;
        }

        if (grid[x - i][y] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x - i][y] != TO_REVERSE_SG(glyph))
        {
            if (grid[x - i][y] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
                if (grid[x - i + 1][y] == SG_EMPTY && i > 1)
                    break;
            }
        }
        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && x - i - 1 > 0)
        {
            if (grid[x - i - 1][y] == TO_REVERSE_SG(glyph))
            {
                countreverseglyph++;
            }
        }
    }
    // 열린 3인 경우
    if (countempty - countreverseglyph > 3 && opencheck == 1 && countglyph == 3)
    {
        check__33 += 1;
    }  // 가로 방향 33

    // 세로 
    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;
    opencheck = 0;

    // 세로 아래 방향 체크
    for (int i = 1; i < 4; i++)
    {

        if (y + i > height - 1)
        {
            break;
        }

        if (grid[x][y + i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x][y + i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x][y + i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
                if (grid[x][y+i-1] == SG_EMPTY && i > 1)
                    break;
            }
        }

        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && y + i + 1 < height)
        {
            if (grid[x][y + i + 1] == TO_REVERSE_SG(glyph))
            {
                countreverseglyph++;
            }
        }
    }

    // 한쪽이 열린 3인지 체킹
    if (countempty > countreverseglyph)
    {
        opencheck += 1;
    }


    // 세로 위 방향
    for (int i = 1; i < 4; i++)
    {

        if (y - i < 0)
        {
            break;
        }

        if (grid[x][y - i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x][y - i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x][y - i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
                if (grid[x][y-i+1] == SG_EMPTY && i > 1)
                    break;
            }
        }
        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && y - i - 1 < height)
        {
            if (grid[x][y - i - 1] == TO_REVERSE_SG(glyph))
            {
                countreverseglyph++;
            }
        }
    }
    // 열린 3인 경우
    if (countempty - countreverseglyph > 3 && opencheck == 1 && countglyph == 3)
    {
        check__33 += 1;
    }  // 세로 방향 33

    // 우측으로 떨어지는 대각선

    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;
    opencheck = 0;

    // 대각선 아래쪽 
    for (int i = 1; i < 4; i++)
    {

        if (x + i > width - 1 || y + i > height - 1)
        {
            break;
        }

        if (grid[x + i][y + i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x + i][y + i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x + i][y + i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
                if (grid[x+i-1][y+i-1] == SG_EMPTY && i > 1)
                    break;
            }
        }

        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && x + i + 1 < width && y + i + 1 < height)
        {
            if (grid[x + i + 1][y + i + 1] == TO_REVERSE_SG(glyph))
            {
                countreverseglyph++;
            }
        }
    }

    // 한쪽이 열린 3인지 체킹
    if (countempty > countreverseglyph)
    {
        opencheck += 1;
    }

    // 대각선 위쪽
    for (int i = 1; i < 4; i++)
    {

        if (x - i < 0 || y - i < 0)
        {
            break;
        }

        if (grid[x - i][y - i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x - i][y - i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x - i][y - i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
                if (grid[x-i+1][y-i+1] == SG_EMPTY && i > 1)
                    break;
               
            }
        }

        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && x - i - 1 > 0 && y - i - 1 > 0)
        {
            if (grid[x - i - 1][y - i - 1] == TO_REVERSE_SG(glyph))
            {
                countreverseglyph++;
            }
        }
    }
    // 열린 3인 경우
    if (countempty - countreverseglyph > 3 && opencheck == 1 && countglyph == 3)
    {
        check__33 += 1;
    }  // 우측으로 떨어지는 대각선 33 판정


    // 좌측으로 떨어지는 대각선
    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;
    opencheck = 0;

    // 대각선 아래 방향
    for (int i = 1; i < 4; i++)
    {

        if (x - i < 0 || y + i > height - 1)
        {
            break;
        }

        if (grid[x - i][y + i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x - i][y + i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x - i][y + i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
                if (grid[x-i+1][y+i-1] == SG_EMPTY && i > 1)
                    break;
            }
        }

        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && x - i - 1 > 0 && y + i + 1 < height)
        {
            if (grid[x - i - 1][y + i + 1] == TO_REVERSE_SG(glyph))
            {
                countreverseglyph++;
            }
        }
    }
    // 한쪽이 열린 3인지 체킹
    if (countempty > countreverseglyph)
    {
        opencheck += 1;
    }

    // 대각선 위 방향
    for (int i = 1; i < 4; i++)
    {

        if (x + i > width - 1 || y - i < 0)
        {
            break;
        }

        if (grid[x + i][y - i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x + i][y - i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x + i][y - i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
                if (grid[x+i-1][y-i+1] == SG_EMPTY && i > 1)
                    break;
            }
        }

        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && x + i + 1 < width && y - i - 1 > 0)
        {
            if (grid[x + i + 1][y - i - 1] == TO_REVERSE_SG(glyph))
            {
                countreverseglyph++;
            }
        }
    }
    // 열린 3인 경우
    if (countempty - countreverseglyph > 3 && opencheck == 1 && countglyph == 3)
    {
        check__33 += 1;
    }  // 좌측으로 떨어지는 대각선 33 판정


    // 3*3 판정에서 가로,세로,우측 대각선, 좌측 대각선에서 2개 이상이 판정 될 경우, 3*3으로 취급하여 금수가 됨.
    if (check__33 >= 2)
    {
        return false;  // 금수 처리
    }

    return true;
}

/**
 * @brief 4*4 조건에 통과되는지 확인한다.
 * @param x 놓는 돌의 x좌표
 * @param y 놓는 돌의 y좌표
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 * @return 정상적인 수면 ture 4*4이면 false
 */
bool check_double_four(char **grid, int width, int height, int x, int y, char glyph)
{
    int countglyph = 1; // 두는 곳은 흑색이므로 1 추가
    int countempty = 0;
    int countreverseglyph = 0;
    int check__44 = 0;
    int opencheck = 0;
    int check_cont_1 = 0;
    int check_jumpglyph_1 = 0;
    int check_cont_2 = 0;
    int check_jumpglyph_2 = 0;

    //가로
    for (int i = 1; i < 5; i++)
    {
        if (x + i > width - 1)
        {
            break;
        }
        if (grid[x + i][y] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x + i][y] != TO_REVERSE_SG(glyph))
        {
            if (grid[x + i][y] == glyph)
            {
                countglyph++;
                if (i > 2 && grid[x + i - 1][y] == glyph && grid[x + i - 2][y] == glyph)
                    check_cont_1++;
                if (i == 2 && grid[x + i - 1][y] == SG_EMPTY)
                    check_jumpglyph_1++;
            }
            else
            {
                countempty++;
                if (grid[x+i-1][y] == SG_EMPTY && i > 1)
                    break;
            }
        }
    }

    for (int i = 1; i < 5; i++)
    {
        if (x - i < 0)
        {
            break;
        }

        if (grid[x - i][y] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x - i][y] != TO_REVERSE_SG(glyph))
        {
            if (grid[x - i][y] == glyph)
            {
                countglyph++;
                if (i > 2 && grid[x - i + 1][y] == glyph && grid[x - i + 2][y] == glyph)
                    check_cont_2++;
                if (i == 2 && grid[x - i + 1][y] == SG_EMPTY)
                    check_jumpglyph_2++;
            }
            else
            {
                countempty++;
                if (grid[x-i+1][y] == SG_EMPTY && i > 1)
                    break;
            }
        }
    }

    // 가로 방향 44
    if (countempty >= countreverseglyph && countglyph == 4)
    {
        check__44 += 1;
    } 
    else if ((check_cont_1 == 1 && check_jumpglyph_2 == 1) || (check_cont_2 == 1 && check_jumpglyph_1))
    {
        check__44 += 1;
    }

    // 세로
    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;
    check_cont_1 = 0;
    check_jumpglyph_1 = 0;
    check_cont_2 = 0;
    check_jumpglyph_2 = 0;

    for (int i = 1; i < 5; i++)
    {
        if (y + i > height - 1)
        {
            break;
        }

        if (grid[x][y + i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x][y + i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x][y + i] == glyph)
            {
                countglyph++;
                if (i > 2 && grid[x][y+i-1] == glyph && grid[x][y+i-2] == glyph)
                    check_cont_1++;
                if (i == 2 && grid[x][y+i-1] == SG_EMPTY)
                    check_jumpglyph_1++;
            }
            else
            {
                countempty++;
                if (grid[x][y+i-1] == SG_EMPTY && i > 1)
                    break;
            }
        }
    }

    for (int i = 1; i < 5; i++)
    {
        if (y - i < 0)
        {
            break;
        }

        if (grid[x][y - i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x][y - i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x][y - i] == glyph)
            {
                countglyph++;
                if (i > 2 && grid[x][y-i+1] == glyph && grid[x][y-i+2] == glyph)
                    check_cont_2++;
                if (i == 2 && grid[x][y-i+1] == SG_EMPTY)
                    check_jumpglyph_2++;
            }
            else
            {
                countempty++;
                if (grid[x][y-i+1] == SG_EMPTY && i > 1)
                    break;
            }
        }
    }

    // 세로 방향 44
    if (countempty >= countreverseglyph && countglyph == 4)
    {
        check__44 += 1;
    } 
    else if ((check_cont_1 == 1 && check_jumpglyph_2 == 1) || (check_cont_2 == 1 && check_jumpglyph_1))
    {
        check__44 += 1;
    }

    // 우측으로 떨어지는 대각선
    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;
    check_cont_1 = 0;
    check_jumpglyph_1 = 0;
    check_cont_2 = 0;
    check_jumpglyph_2 = 0;

    // 대각선 아래

    for (int i = 1; i < 5; i++)
    {
        if (y + i > height - 1 || x + i > width - 1)
        {
            break;
        }

        if (grid[x + i][y + i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x + i][y + i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x + i][y + i] == glyph)
            {
                countglyph++;
                if (i > 2 && grid[x + i - 1][y+i-1] == glyph && grid[x + i - 2][y+i-1] == glyph)
                    check_cont_1++;
                if (i == 2 && grid[x + i - 1][y+i-1] == SG_EMPTY)
                    check_jumpglyph_1++;
            }
            else
            {
                countempty++;
                if (grid[x+i-1][y+i-1] == SG_EMPTY && i > 1)
                    break;
            }
        }
    }

    // 대각선 위

    for (int i = 1; i < 5; i++)
    {
        if (y - i < 0 || x - i < 0)
        {
            break;
        }

        if (grid[x - i][y - i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x - i][y - i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x - i][y - i] == glyph)
            {
                countglyph++;
                if (i > 2 && grid[x - i + 1][y-i+1] == glyph && grid[x - i + 2][y-i+2] == glyph)
                    check_cont_2++;
                if (i == 2 && grid[x - i + 1][y-i+1] == SG_EMPTY)
                    check_jumpglyph_2++;
            }
            else
            {
                countempty++;
                if (grid[x-i+1][y-i+1] == SG_EMPTY && i > 1)
                    break;
            }
        }
    }

    // 우측으로 떨어지는 대각선 44
    if (countempty >= countreverseglyph && countglyph == 4)
    {
        check__44 = 1;
    }  
    else if ((check_cont_1 == 1 && check_jumpglyph_2 == 1) || (check_cont_2 == 1 && check_jumpglyph_1))
    {
        check__44 += 1;
    }

    // 좌측으로 떨어지는 대각선

    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;
    check_cont_1 = 0;
    check_jumpglyph_1 = 0;
    check_cont_2 = 0;
    check_jumpglyph_2 = 0;

    // 대각선 아래

    for (int i = 1; i < 5; i++)
    {
        if (x - i < 0 || y + i > height -1)
        {
            break;
        }

        if (grid[x - i][y + i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x - i][y + i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x - i][y + i] == glyph)
            {
                countglyph++;
                if (i > 2 && grid[x - i + 1][y+i-1] == glyph && grid[x - i + 2][y+i-2] == glyph)
                    check_cont_1++;
                if (i == 2 && grid[x - i + 1][y+i-2] == SG_EMPTY)
                    check_jumpglyph_1++;
            }
            else
            {
                countempty++;
                if (grid[x-i+1][y+i-1] == SG_EMPTY && i > 1)
                    break;
            }
        }
    }

    // 대각선 위

    for (int i = 1; i < 5; i++)
    {
        if (x + i > width - 1 || y - i < 0)
        {
            break;
        }

        if (grid[x + i][y - i] == TO_REVERSE_SG(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x + i][y - i] != TO_REVERSE_SG(glyph))
        {
            if (grid[x + i][y - i] == glyph)
            {
                countglyph++;
                if (i > 2 && grid[x + i - 1][y-i+1] == glyph && grid[x + i - 2][y-i+2] == glyph)
                    check_cont_2++;
                if (i == 2 && grid[x + i - 1][y-i+1]== SG_EMPTY)
                    check_jumpglyph_2++;
            }
            else
            {
                countempty++;
                if (grid[x+i-1][y-i+1] == SG_EMPTY && i > 1)
                    break;
            }
        }
    }

    // 좌측으로 떨어지는 대각선 방향 44
    if (countempty >= countreverseglyph && countglyph == 4)
    {
        check__44 = 1;  

    }
    else if ((check_cont_1 == 1 && check_jumpglyph_2 == 1) || (check_cont_2 == 1 && check_jumpglyph_1))
    {
        check__44 += 1;
    }

    else if (check__44 >= 2)
    {
        return false;  //  // 4*4 판정에서 가로,세로,우측 대각선, 좌측 대각선에서 2개 이상이 판정 될 경우, 4*4으로 취급하여 금수가 됨.
    }

    char** copygrid = generate_grid(width, height);

    copy_grid(grid, copygrid, width, height, glyph);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            copygrid[i][j] = grid[i][j];
        }
    }

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
            copygrid[x][i + 6] == glyph && copygrid[x][i + 7] == glyph&&
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
                copygrid[j + 7][i + 7] == glyph&& ((j != 0 && i != 0 && copygrid[j - 1][i - 1] != glyph) &&
                    (j != width - 8 && i != height - 8 && copygrid[j + 8][i + 8] != glyph)))
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
                copygrid[j + 7][i - 7] == glyph&& ((j != 0 && i != height-1 && copygrid[j - 1][i + 1] != glyph) && 
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
            copygrid[j + 6][y] == glyph)&&((j != 0 && copygrid[j - 1][y] != glyph) && (j != width - 7 && copygrid[j + 7][y] != glyph)))
        {
            free_double_pointer(copygrid, width);
            return false;
        }

    }


    for (int i = 0; i < height - 6; i++) // 세로
    {
        if ((copygrid[x][i] == glyph && copygrid[x][i + 1] == SG_EMPTY && copygrid[x][i + 2] == glyph &&
            copygrid[x][i + 3] == glyph && copygrid[x][i + 4] == glyph && copygrid[x][i + 5] == SG_EMPTY &&
            copygrid[x][i + 6] == glyph)&&((i != 0 && copygrid[x][i-1] != glyph) && (i != height - 7 && copygrid[x][i+7] != glyph)))
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
                copygrid[j + 5][i + 5] == SG_EMPTY && copygrid[j + 6][i + 6] == glyph&&
                ((j != 0 && i !=0 && copygrid[j-1][i-1] != glyph) && (j != width-7 &&i != height - 7 && copygrid[j+7][i + 7] != glyph)))
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
                copygrid[j + 5][i - 5] == SG_EMPTY && copygrid[j + 6][i - 6] == glyph&&
                ((j != 0 && i != height-1 && copygrid[j - 1][i + 1] != glyph) && (j != width - 7 && i != 6 && copygrid[j + 7][i - 7] != glyph)))
            {
                free_double_pointer(copygrid, width);
                return false;
            }
        }
    }

    free_double_pointer(copygrid, width);
    return true;
}

/**
 * @brief 장목인지 확인한다.
 * @param x 놓는 돌의 x좌표
 * @param y 놓는 돌의 y좌표
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 * @return 정상적인 수면 ture 장목이면 false
 */
bool check_overline(char **grid, int width, int height, int x, int y, char glyph)
{
    char **copygrid = generate_grid(width, height);
    copy_grid(grid, copygrid, width, height);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            copygrid[i][j] = grid[i][j];
            if (copygrid[i][j] != glyph && copygrid[i][j] != TO_REVERSE_SG(glyph))
            {
                copygrid[i][j] = SG_EMPTY;
            }
        }
    }

    copygrid[x][y] = glyph;

    for (int j = 0; j < width - 5; j++) // 가로
    {
        if (copygrid[j][y] == glyph && copygrid[j + 1][y] == glyph && copygrid[j + 2][y] == glyph &&
            copygrid[j + 3][y] == glyph && copygrid[j + 4][y] == glyph && copygrid[j + 5][y] == glyph)
        {
            free_double_pointer(copygrid, width);
            return false;
        }

    }


    for (int i = 0; i < height - 5; i++) // 세로
    {
        if (copygrid[x][i] == glyph && copygrid[x][i + 1] == glyph && copygrid[x][i + 2] == glyph &&
            copygrid[x][i + 3] == glyph && copygrid[x][i + 4] == glyph && copygrid[x][i + 5] == glyph)
        {
            free_double_pointer(copygrid, width);
            return false;
        }

    }

    for (int j = 0; j < width - 5; j++) // 우측으로 떨어지는 대각선
    {
        for (int i = 0; i < height - 5; i++)
        {
            if (copygrid[j][i] == glyph && copygrid[j + 1][i + 1] == glyph && copygrid[j + 2][i + 2] == glyph &&
                copygrid[j + 3][i + 3] == glyph && copygrid[j + 4][i + 4] == glyph && copygrid[j + 5][i + 5] == glyph)
            {
                free_double_pointer(copygrid, width);
                return false;
            }
        }
    }
    for (int j = 0; j < width - 5; j++) // 좌측으로 떨어지는 대각선
    {
        for (int i = 5; i < height; i++)
        {
            if (copygrid[j][i] == glyph && copygrid[j + 1][i - 1] == glyph && copygrid[j + 2][i - 2] == glyph &&
                copygrid[j + 3][i - 3] == glyph && copygrid[j + 4][i - 4] == glyph && copygrid[j + 5][i - 5] == glyph)
            {
                free_double_pointer(copygrid, width);
                return false;
            }
        }
    }
    free_double_pointer(copygrid, width);
    return true;
}

/**
 * @brief 렌주룰 조건을 모두 확인하여, 둘 수 있는 수인지 확인한다.
 * @param x 놓는 돌의 x좌표
 * @param y 놓는 돌의 y좌표
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 * @return 정상적인 수면 ture 둘 수 없다면 false
 */
bool check_confirm(char **grid, int width, int height, int x, int y, char glyph)
{
    if (glyph == SG_BLACK)
    {
        if (check_double_three(grid, width, height, x, y, glyph) &&
            check_double_four(grid, width, height, x, y, glyph) && check_overline(grid, width, height, x, y, glyph))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (glyph == SG_WHITE)
    {
        return true;
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
        for (int a = 0; a < n+1; a++)
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
        for (int a = 0; a < n+1; a++)
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
            for (int a = 0; a < n+1; a++)
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
            for (int a = 0; a < n+1; a++)
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