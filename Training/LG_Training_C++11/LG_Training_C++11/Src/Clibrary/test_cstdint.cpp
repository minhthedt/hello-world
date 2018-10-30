#include "test_cstdint.h"
#include <stdio.h>
#include <cstdint> //(stdint.h) C++11
#include <cstdbool>

void test_cstdint()
{
    
    intmax_t max;
    uint_least8_t* var = new uint_least8_t;
    *var = 154;
    intptr_t ptr = (intptr_t)var; // convert pointer to int (intptr_t) ptr = address of allocated memory
    printf("intptr_t ptr = 0x%x\n", ptr);

    uint_least8_t* var_cast = reinterpret_cast<uint_least8_t*>(ptr); // convert int to pointer (intptr_t)
    printf("var_cast = %d\n",*var_cast);
   
    printf("sizeof(uint_least8_t) = %d\n", sizeof(uint_least8_t));
    printf("sizeof(uint_least16_t) = %d\n", sizeof(uint_least16_t));
    printf("sizeof(uint_least32_t) = %d\n", sizeof(uint_least32_t));
}