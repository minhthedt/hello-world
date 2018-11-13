#include <stdio.h>
#include <iostream>


extern void test_constexp();
extern void test_binary_literal();
extern void test_generic_lambda();
extern void test_lambda_capture();
extern void test_decltype_auto();
extern void test_variable_template();

void test_user_defined_literal();


void main(int argn, char** argv)
{
    //printf("_MSC_VER = %d\n", _MSC_VER);
    //test_constexp();
    //test_binary_literal();
    //test_generic_lambda();
    //test_lambda_capture();
    //test_decltype_auto();
    //test_decltype_auto();
    //test_variable_template();

    test_user_defined_literal();

    getchar();
}