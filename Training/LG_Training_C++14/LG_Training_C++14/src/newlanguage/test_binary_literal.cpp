#include "test_binary_literal.h"
#include <stdio.h>

void test_binary_literal()
{
    int d = 42; //decimal-literal //base 10
    int o = 052; //octal-literal  //base 8
    int x = 0x2a; //hex-literal   //base 16
    int X = 0X2A; //hex - literal //base 16
    int b = 0b101010; //binary-literal C++14 //base 2

    // unsigned long long int
    unsigned long long  l1 = 18446744073709550592ull; // C++11
   
    //Digit separators
    //In C++14, the single-quote character may be used arbitrarily as a digit separator in numeric literals, both integer literals and floating point literals.
    //[11] This can make it easier for human readers to parse large numbers through subitizing.
    unsigned long long  l2 = 18'446'744'073'709'550'592llu; // C++14 //it easier for human readers 
    int bb = 0b1010'1000'1000'1000'1000'1000'1000'1000;
    float f = 0.10123f;
    int ff = 0xabcd'12 + 112;
    printf("bb = %b\n", bb);
    printf("o = %d\n", o);
    printf("l2 = %llu\n", l1);


}
