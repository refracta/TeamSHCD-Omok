 /**
  @file gamecore.c
  @brief 게임 코어
*/
#include <stdlib.h>
#include <stdbool.h>
#include "inc/gamecore.h"

/**
* @brief 동적 할당을 통해 이차원 배열처럼 쓸 수 있는 이중 포인터를 반환한다.
* @param type_size 이중 포인터의 타입
* @param width 이중 포인터의 가로 길이
* @param height 이중 포인터의 세로 길이
* @return 이중 포인터
*/
void** malloc_double_pointer(int type_size, int width, int height)
{
    void** grid = malloc(sizeof(void*) * width);
    if (grid == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < width; i++)
    {
        grid[i] = malloc(type_size * height);
        if (grid[i] == NULL)
        {
            return NULL;
        }
    }
    return grid;
}

/**
* @brief 동적 할당을 통해 생성한 이중 포인터를 할당 해제한다.
* @param width 가로 길이
*/
void free_double_pointer(void** grid, int width)
{
    for (int x = 0; x < width; x++)
    {
        free(grid[x]);
    }
    free(grid);
}

/**
* @brief SG_EMPTY로 초기화한 격자를 생성한다.
* @param width 격자의 가로 길이
* @param width 격자의 세로 길이
* @return 격자 이중 포인터
*/
char** generate_grid(int width, int height)
{
    char** grid = (char**)malloc_double_pointer(sizeof(char), width, height);
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
 * @brief glyph의 반대 색깔은 알아낸다.
 * @return glyph의 반대 색깔을 리턴한다.
 */
char reverse_glyph(char glyph)
{
    return (glyph == SG_BLACK ? SG_WHITE : SG_BLACK);
}

/**
 * @brief 격자의 복사본을 만든다.
 * @param copygrid 격자의 카피본
 * @param glyph 돌의 색깔
 * @param width 격자의 가로 길이
 * @param height 격자의 세로 길이
 */
void copy_grid(char** grid, char** copygrid, int width, int height, char glyph)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            copygrid[i][j] = grid[i][j];
            if (copygrid[i][j] != glyph && copygrid[i][j] != reverse_glyph(glyph))
                copygrid[i][j] = SG_EMPTY;
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
bool check_double_three(char** grid, int width, int height, int x, int y, char glyph)
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
        if (x + i > 18)
            break;

        if (grid[y][x + i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[y][x + i] != reverse_glyph(glyph))
        {
            if (grid[y][x + i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && x + i + 1 < 19)
            if (grid[y][x + i + 1] == reverse_glyph(glyph))
                countreverseglyph++;
    }

    // 한쪽이 열린 3인지 체킹
    if (countempty > countreverseglyph)
        opencheck = 1;

    // 가로 좌측 방향 체크
    for (int i = 1; i < 4; i++)
    {
        if (x - i < 0)
            break;

        if (grid[y][x - i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[y][x - i] != reverse_glyph(glyph))
        {
            if (grid[y][x - i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && x - i - 1 > 0)
            if (grid[y][x - i - 1] == reverse_glyph(glyph))
                countreverseglyph++;
    }
    // 열린 3인 경우
    if (countempty - countreverseglyph > 3 && opencheck == 1 && countglyph == 3)
        check__33 += 1;  // 가로 방향 33

    // 세로 
    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;
    opencheck = 0;

    // 세로 아래 방향 체크
    for (int i = 1; i < 4; i++)
    {

        if (y + i > 18)
            break;

        if (grid[y + i][x] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[y + i][x] != reverse_glyph(glyph))
        {
            if (grid[y + i][x] == reverse_glyph(glyph))
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && y + i + 1 < 19)
            if (grid[y + i + 1][x] == reverse_glyph(glyph))
                countreverseglyph++;
    }

    // 한쪽이 열린 3인지 체킹
    if (countempty > countreverseglyph)
        opencheck = 1;



    // 세로 위 방향
    for (int i = 1; i < 4; i++)
    {

        if (y - i < 0)
            break;

        if (grid[y - i][x] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[y - i][x] != reverse_glyph(glyph))
        {
            if (grid[y - i][x] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && y - i - 1 < 0)
            if (grid[y - i - 1][x] == reverse_glyph(glyph))
                countreverseglyph++;
    }

    // 열린 3인 경우
    if (countempty - countreverseglyph > 3 && opencheck == 1 && countglyph == 3)
        check__33 += 1;  // 세로 방향 33 


    // 우측으로 떨어지는 대각선

    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;
    opencheck = 0;

    // 대각선 아래쪽 
    for (int i = 1; i < 4; i++)
    {

        if (y + i > 18 || x + i > 18)
            break;

        if (grid[y + i][x + i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[y + i][x + i] != reverse_glyph(glyph))
        {
            if (grid[y + i][x + i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }

        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && y + i + 1 < 19 && x + i + 1 < 19)
            if (grid[y + i + 1][x + i + 1] == reverse_glyph(glyph))
                countreverseglyph++;
    }

    // 한쪽이 열린 3인지 체킹
    if (countempty > countreverseglyph)
        opencheck = 1;

    // 대각선 위쪽
    for (int i = 1; i < 4; i++)
    {

        if (y - i < 0 || x - i < 0)
            break;

        if (grid[y - i][x - i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[y - i][x - i] != reverse_glyph(glyph))
        {
            if (grid[y - i][x - i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }

        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && y - i - 1 > 0 && x - i - 1 > 0)
            if (grid[y - i - 1][x - i - 1] == reverse_glyph(glyph))
                countreverseglyph++;
    }
    // 열린 3인 경우
    if (countempty - countreverseglyph > 3 && opencheck == 1 && countglyph == 3)
        check__33 += 1;  // 우측으로 떨어지는 대각선 33 판정


    // 좌측으로 떨어지는 대각선
    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;
    opencheck = 0;

    // 대각선 아래 방향
    for (int i = 1; i < 4; i++)
    {

        if (y + i > 18 || x - i < 0)
            break;

        if (grid[y + i][x - i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[y + i][x - i] != reverse_glyph(glyph))
        {
            if (grid[y + i][x - i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }

        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && y + i + 1 < 19 && x - i - 1 > 0)
            if (grid[y + i + 1][x - i - 1] == reverse_glyph(glyph))
                countreverseglyph++;
    }
    // 한쪽이 열린 3인지 체킹
    if (countempty > countreverseglyph)
        opencheck = 1;

    // 대각선 위 방향
    for (int i = 1; i < 4; i++)
    {

        if (y - i < 0 || x + i >18)
            break;

        if (grid[y - i][x + i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[y - i][x + i] != reverse_glyph(glyph))
        {
            if (grid[y - i][x + i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }

        // 4번째 칸이 백돌일 경우 추가 진행
        if (i == 3 && y - i - 1 > 0 && x + i + 1 < 19)
            if (grid[y - i - 1][x + i + 1] == reverse_glyph(glyph))
                countreverseglyph++;
    }
    // 열린 3인 경우
    if (countempty - countreverseglyph > 3 && opencheck == 1 && countglyph == 3)
        check__33 += 1;  // 좌측으로 떨어지는 대각선 33 판정


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
bool check_double_four(char** grid, int width, int height, int x, int y, char glyph)
{
    int countglyph = 1; // 두는 곳은 흑색이므로 1 추가
    int countempty = 0;
    int countreverseglyph = 0;
    int check__44 = 0;
    int opencheck = 0;

    //가로
    for (int i = 1; i < 5; i++) {
        if (x + i > 18)
            break;
        if (grid[x + i][y] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x + i][y] != reverse_glyph(glyph))
        {
            if (grid[x + i][y] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
    }

    for (int i = 1; i < 5; i++)
    {
        if (x - i < 0)
            break;

        if (grid[x - i][y] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x - i][y] != reverse_glyph(glyph))
        {
            if (grid[x - i][y] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
    }

    // 열린 4인 경우
    if (countempty >= countreverseglyph && countglyph == 4)
        check__44 += 1;  // 가로 방향 44 

    // 세로
    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;

    for (int i = 1; i < 5; i++)
    {
        if (y + i > 18)
            break;

        if (grid[x][y + i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x][y + i] != reverse_glyph(glyph))
        {
            if (grid[x][y + i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
    }

    for (int i = 1; i < 5; i++)
    {
        if (y - i < 0)
            break;

        if (grid[x][y - i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x][y - i] != reverse_glyph(glyph))
        {
            if (grid[x][y - i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
    }

    // 열린 4인 경우
    if (countempty >= countreverseglyph && countglyph == 4)
        check__44 += 1; // 세로 방향 44 

    // 우측으로 떨어지는 대각선
    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;

    // 대각선 아래

    for (int i = 1; i < 5; i++)
    {
        if (y + i > 18 || x + i > 18)
            break;

        if (grid[x + i][y + i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x + i][y + i] != reverse_glyph(glyph))
        {
            if (grid[x + i][y + i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
    }

    // 대각선 위

    for (int i = 1; i < 5; i++)
    {
        if (y - i < 0 || x - i < 0)
            break;

        if (grid[x - i][y - i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x - i][y - i] != reverse_glyph(glyph))
        {
            if (grid[x - i][y - i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
    }

    // 열린 4인 경우
    if (countempty >= countreverseglyph && countglyph == 4)
        check__44 = 1;  // 우측으로 떨어지는 대각선 44 

    // 좌측으로 떨어지는 대각선

    countglyph = 1;
    countempty = 0;
    countreverseglyph = 0;

    // 대각선 아래

    for (int i = 1; i < 5; i++)
    {
        if (y + i > 18 || x - i < 0)
            break;

        if (grid[x - i][y + i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x - i][y + i] != reverse_glyph(glyph))
        {
            if (grid[x - i][y + i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
    }

    // 대각선 위

    for (int i = 1; i < 5; i++)
    {
        if (y - i < 0 || x + i > 18)
            break;

        if (grid[x + i][y - i] == reverse_glyph(glyph))
        {
            countreverseglyph++;
            break;
        }
        else if (grid[x + i][y - i] != reverse_glyph(glyph))
        {
            if (grid[x + i][y - i] == glyph)
            {
                countglyph++;
            }
            else
            {
                countempty++;
            }
        }
    }

    // 열린 4인 경우
    if (countempty >= countreverseglyph && countglyph == 4)
        check__44 = 1;  // 좌측으로 떨어지는 대각선 방향 44 

        // 4*4 판정에서 가로,세로,우측 대각선, 좌측 대각선에서 2개 이상이 판정 될 경우, 4*4으로 취급하여 금수가 됨.
    else if (check__44 >= 2)
    {
        return false;  // 금수 처리
    }

    char** copygrid = generate_grid(width, height);

    copy_grid(grid, copygrid, width, height, glyph);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            copygrid[i][j] = grid[i][j];

            if (copygrid[i][j] != glyph && copygrid[i][j] != reverse_glyph(glyph))
                copygrid[i][j] = SG_EMPTY;
        }
    }

    copygrid[x][y] = glyph;
    // 추가 경우의 수
    // B B 빈칸 B B 빈칸 B B
    for (int j = 0; j < width - 7; j++) // 세로
    {
        if (copygrid[j][y] == glyph && copygrid[j + 1][y] == glyph && copygrid[j + 2][y] == SG_EMPTY && copygrid[j + 3][y] == glyph && copygrid[j + 4][y] == glyph && copygrid[j + 5][y] == SG_EMPTY && copygrid[j + 6][y] == glyph && copygrid[j + 7][y] == glyph)
        {
            free_double_pointer(copygrid, width);
            return false;
        }

    }

    for (int i = 0; i < height - 7; i++) // 가로
    {
        if (copygrid[x][i] == glyph && copygrid[x][i + 1] == glyph && copygrid[x][i + 2] == SG_EMPTY && copygrid[x][i + 3] == glyph && copygrid[x][i + 4] == glyph && copygrid[x][i + 5] == SG_EMPTY && copygrid[x][i + 6] == glyph && copygrid[x][i + 7] == glyph)
        {
            free_double_pointer(copygrid, width);
            return false;
        }

    }

    for (int j = 0; j < width - 7; j++) // 우측으로 떨어지는 대각선
    {
        for (int i = 0; i < height - 7; i++)
        {
            if (copygrid[j][i] == glyph && copygrid[j + 1][i + 1] == glyph && copygrid[j + 2][i + 2] == SG_EMPTY && copygrid[j + 3][i + 3] == glyph && copygrid[j + 4][i + 4] == glyph && copygrid[j + 5][i + 5] == SG_EMPTY && copygrid[j + 6][i + 6] == glyph && copygrid[j + 7][i + 7] == glyph)
            {
                free_double_pointer(copygrid, width);
                return false;
            }

        }
    }
    for (int j = 0; j < width-7; j++) // 좌측으로 떨어지는 대각선
    {
        for (int i = 7; i < height; i++)
        {
            if (copygrid[j][i] == glyph && copygrid[j + 1][i - 1] == glyph && copygrid[j + 2][i - 2] == SG_EMPTY && copygrid[j + 3][i - 3] == glyph && copygrid[j + 4][i - 4] == glyph && copygrid[j + 5][i - 5] == SG_EMPTY && copygrid[j + 6][i - 6] == glyph && copygrid[j + 7][i - 7] == glyph)
            {
                free_double_pointer(copygrid, width);
                return false;
            }

        }
    }

    // B 빈칸 B B B 빈칸 B

    for (int j = 0; j < width - 6; j++) // 가로
    {
        if (copygrid[j][y] == glyph && copygrid[j + 1][y] == SG_EMPTY && copygrid[j + 2][y] == glyph && copygrid[j + 3][y] == glyph && copygrid[j + 4][y] == glyph && copygrid[j + 5][y] == SG_EMPTY && copygrid[j + 6][y] == glyph)
        {
            free_double_pointer(copygrid, width);
            return false;
        }

    }


    for (int i = 0; i < height - 6; i++) // 세로
    {
        if (copygrid[x][i] == glyph && copygrid[x][i + 1] == SG_EMPTY && copygrid[x][i + 2] == glyph && copygrid[x][i + 3] == glyph && copygrid[x][i + 4] == glyph && copygrid[x][i + 5] == SG_EMPTY && copygrid[x][i + 6] == glyph)
        {
            free_double_pointer(copygrid, width);
            return false;
        }

    }

    for (int j = 0; j < width - 6; j++) // 우측으로 떨어지는 대각선
    {
        for (int i = 0; i < height - 6; i++)
        {
            if (copygrid[j][i] == glyph && copygrid[j + 1][i + 1] == SG_EMPTY && copygrid[j + 2][i + 2] == glyph && copygrid[j + 3][i + 3] == glyph && copygrid[j + 4][i + 4] == glyph && copygrid[j + 5][i + 5] == SG_EMPTY && copygrid[j + 6][i + 6] == glyph)
            {
                free_double_pointer(copygrid, width);
                return false;
            }

        }
    }
    for (int j = 0; j < width-6; j++) // 좌측으로 떨어지는 대각선
    {
        for (int i = 6; i < height; i++)
        {
            if (copygrid[j][i] == glyph && copygrid[j + 1][i - 1] == SG_EMPTY && copygrid[j + 2][i - 2] == glyph && copygrid[j + 3][i - 3] == glyph && copygrid[j + 4][i - 4] == glyph && copygrid[j + 5][i - 5] == SG_EMPTY && copygrid[j + 6][i - 6] == glyph)
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
bool check_overline(char** grid, int width, int height, int x, int y, char glyph)
{
    char** copygrid = generate_grid(width, height);
    copy_grid(grid, copygrid, width, height, glyph);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            copygrid[i][j] = grid[i][j];
            if (copygrid[i][j] != glyph && copygrid[i][j] != reverse_glyph(glyph))
                copygrid[i][j] = SG_EMPTY;
        }
    }

    copygrid[x][y] = glyph;

    for (int j = 0; j < width - 5; j++) // 가로
    {
        if (copygrid[j][y] == glyph && copygrid[j + 1][y] == glyph && copygrid[j + 2][y] == glyph && copygrid[j + 3][y] == glyph && copygrid[j + 4][y] == glyph && copygrid[j + 5][y] == glyph)
        {
            free_double_pointer(copygrid, width);
            return false;
        }

    }


    for (int i = 0; i < height - 5; i++) // 세로
    {
        if (copygrid[x][i] == glyph && copygrid[x][i + 1] == glyph && copygrid[x][i + 2] == glyph && copygrid[x][i + 3] == glyph && copygrid[x][i + 4] == glyph && copygrid[x][i + 5] == glyph)
        {
            free_double_pointer(copygrid, width);
            return false;
        }

    }

    for (int j = 0; j < width - 5; j++) // 우측으로 떨어지는 대각선
    {
        for (int i = 0; i < height - 5; i++)
        {
            if (copygrid[j][i] == glyph && copygrid[j + 1][i + 1] == glyph && copygrid[j + 2][i + 2] == glyph && copygrid[j + 3][i + 3] == glyph && copygrid[j + 4][i + 4] == glyph && copygrid[j + 5][i + 5] == glyph)
            {
                free_double_pointer(copygrid, width);
                return false;
            }
        }
    }
    for (int j = 0; j < width-5; j++) // 좌측으로 떨어지는 대각선
    {
        for (int i = 5; i < height ; i++)
        {
            if (copygrid[j][i] == glyph && copygrid[j + 1][i - 1] == glyph && copygrid[j + 2][i - 2] == glyph && copygrid[j + 3][i - 3] == glyph && copygrid[j + 4][i - 4] == glyph && copygrid[j + 5][i - 5] == glyph)
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
bool check_confirm(char** grid, int width, int height, int x, int y, char glyph)
{
    if (glyph == SG_BLACK)
    {
        if (check_double_three(grid, width, height, x, y, glyph) && check_double_four(grid, width, height, x, y, glyph) && check_overline(grid, width, height, x, y, glyph))
            return true;
        else
            return false;
    }
    else if (glyph == SG_WHITE)
        return true;
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
bool Win_nmok(char** grid, int n, int width, int height, int x, int y, char glyph)
{
    int checkglyph = 0;
    for (int i = 0; i < width - (n - 1); i++)
    {
        for (int a = 0; a < n; a++)
        {
            if (grid[i + a][y] == glyph)
                checkglyph++;
            else
                break;
        }
        if (checkglyph == n)
            return true;
    }

    checkglyph = 0;
    for (int i = 0; i < height - (n - 1); i++)
    {
        for (int a = 0; a < n; a++)
        {
            if (grid[x][i + a] == glyph)
                checkglyph++;
            else
                break;
        }
        if (checkglyph == n)
            return true;

    }

    checkglyph = 0;
    for (int i = 0; i < width - (n - 1); i++)
    {
        for (int j = 0; j < height - (n - 1); j++)
        {
            for (int a = 0; a < n; a++)
            {
                if (grid[i + a][j + a] == glyph)
                    checkglyph++;
                else
                    break;
            }
            if (checkglyph == n)
                return true;
        }
    }

    checkglyph = 0;
    for (int i = 0; i < width - (n - 1); i++)
    {
        for (int j = (n - 1); j < height; j++)
        {
            for (int a = 0; a < n; a++)
            {
                if (grid[i + a][j - a] == glyph)
                    checkglyph++;
                else
                    break;
            }
            if (checkglyph == n)
                return true;
        }
    }

    return false;
}