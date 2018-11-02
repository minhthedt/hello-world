#include "test_cuchar.h"
#include <wchar.h>
#include <uchar.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef MB_CUR_MAX
#undef MB_CUR_MAX
#endif

#undef MB_CUR_MAX

#define MB_CUR_MAX 1024

void test_cuchar()
{
    const char16_t* pt = u"Juan Souli\u00e9";
    char buffer[MB_CUR_MAX];
    int i;
    size_t length;
    mbstate_t mbs;

    mbrlen(NULL, 0, &mbs);   /* initialize mbs */

    while (*pt) {
        length = c16rtomb(buffer, *pt, &mbs);
        if ((length == 0) || (length>MB_CUR_MAX)) break;
        for (i = 0; i<length; ++i) putchar(buffer[i]);
        ++pt;
    }
}