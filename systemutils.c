#include <Windows.h>
#include <time.h>
#include "inc/systemutils.h"

/**
 * @brief �־��� timespec �Ű������� �ð��� ����Ͽ� �����Ѵ�.
 * @param spec timespec
 * @description Source from https://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows
*/
void unix_time(struct timespec* spec) 
{
    __int64 wintime; GetSystemTimeAsFileTime((FILETIME*)&wintime);
    wintime -= w2ux;  spec->tv_sec = wintime / exp7;
    spec->tv_nsec = wintime % exp7 * 100;
}

/**
 * @brief unix �迭���� ����ϴ� clock_gettime�� ������ ����ü
 * @param id clk_id
 * @param spec tp
 * @return errno
 */
int clock_gettime(int id, struct timespec* spec) 
{
    static  struct timespec startspec; static double ticks2nano;
    static __int64 startticks, tps = 0;    __int64 tmp, curticks;
    QueryPerformanceFrequency((LARGE_INTEGER*)&tmp);
    if (tps != tmp) 
    {
        tps = tmp;
        QueryPerformanceCounter((LARGE_INTEGER*)&startticks);
        unix_time(&startspec); ticks2nano = (double)exp9 / tps;
    }
    QueryPerformanceCounter((LARGE_INTEGER*)&curticks); curticks -= startticks;
    spec->tv_sec = startspec.tv_sec + (curticks / tps);
    spec->tv_nsec = startspec.tv_nsec + (double)(curticks % tps) * ticks2nano;
    if (!(spec->tv_nsec < exp9)) 
    { 
        spec->tv_sec++; spec->tv_nsec -= exp9; 
    }
    return 0;
}


/**
 * @brief ������ �ð����� ����Ѵ�. 
 * @param ms ����� �ð� (�и���)
 */
void wait(unsigned long ms) 
{
    Sleep(ms);
}