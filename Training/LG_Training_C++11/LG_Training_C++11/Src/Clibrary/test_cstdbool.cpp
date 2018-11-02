#include "test_cstdbool.h"
#include <stdio.h>
#include <stdbool.h>

void test_cstdbool()
{
#ifdef bool_true_false_are_defined
    printf("bool_true_false_are_defined was defined");
#else
    printf("bool_true_false_are_defined was NOT defined");
#endif
}