#include <stdio.h>
extern void test_cfenv();

int main(char argn, char** argv)
{
    test_cfenv();
    getchar();
    return 0;
}
