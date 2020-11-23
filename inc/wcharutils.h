#ifndef WCHARUTILS_H
#define WCHARUTILS_H

#include <stdbool.h>
#include <wchar.h>

bool is_full_width(wchar_t c);

int strrlen(wchar_t *s);

#endif