/* feclearexcept, fetestexcept example */
#include "test_cfenv.h"
#include <stdio.h>      /* printf */
#if _MSC_VER > 1800
#include <math.h>       /* sqrt */
#else
#include <cmath>       /* sqrt */
#endif
#include <fenv.h>       /* feclearexcept, fetestexcept, FE_ALL_EXCEPT, FE_INVALID */ //(fenv.h) C++11
#pragma STDC FENV_ACCESS on

double fn(double x) {  /* some function for which zero is a domain error */
    //Raise floating-point exception
    if (x == 0.0) feraiseexcept(FE_INVALID);
    return x;
}

void test_cfenv()
{
    //1.0 Clear floating-point exceptions
    feclearexcept(FE_ALL_EXCEPT);
    int a = -1;
    sqrt(a);
    //Test for floating-point exceptions
    if (fetestexcept(FE_INVALID)) printf("sqrt(-1) raises FE_INVALID\n");

    //2.0 
    feclearexcept(FE_ALL_EXCEPT);
    fn(0.0);
    if (fetestexcept(FE_INVALID)) printf("FE_INVALID raised\n");

    //3.0 fegetround
    printf("rounding using ");
    switch (fegetround()) 
    {
        case FE_DOWNWARD: printf("downward"); break;
        case FE_TONEAREST: printf("to-nearest"); break;//to-nearest
        case FE_TOWARDZERO: printf("toward-zero"); break;
        case FE_UPWARD: printf("upward"); break;
        default: printf("unknown");
    }

    printf(" rounding:\n");

    printf("rint (2.3) = %.1f\n", rint(2.3));//2.0
    printf("rint (3.8) = %.1f\n", rint(3.8));//4.0
    printf("rint (-2.3) = %.1f\n", rint(-2.3));//2.0
    printf("rint (-3.8) = %.1f\n", rint(-3.8));//-4.0

}