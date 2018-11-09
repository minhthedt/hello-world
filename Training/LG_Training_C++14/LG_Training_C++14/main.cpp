#include <stdio.h>
#include <iostream>


extern void test_constexp();

void main(int argn, char** argv)
{

    test_constexp();
    printf("helloworld");
    getchar();
}