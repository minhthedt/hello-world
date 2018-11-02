#include "test_cinttypes.h"
#include <stdio.h>
#include <cinttypes> //(inttypes.h) C++11 , 
//Including this header automatically includes also <cstdint> (which defines width-based integral types).

void test_cinttypes()
{
    char buffer[80];
    intmax_t foo, bar;

    printf("Please, enter a number: ");
    fgets(buffer, 80, stdin);
    foo = strtoimax(buffer, NULL, 10);

    printf("Thanks for entering %" PRIdMAX ".\n", foo);//#define PRIdMAX "lld"

    printf("Please, enter another number: ");
    scanf_s("%" SCNdMAX, &bar);//#define SCNdMAX  "lld"

    printf("%" PRIdMAX " by %" PRIdMAX " is %" PRIdMAX, foo, bar, foo*bar);
}