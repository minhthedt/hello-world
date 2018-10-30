#include <stdio.h>
extern void test_cfenv();
extern void test_cstdint();
extern void test_cuchar();//??
extern void test_ctgmath();
extern void test_forward_list();
extern void test_unordered_map();
extern void test_unordered_set();

extern void test_ratio();
extern void test_chrono();

int main(char argn, char** argv)
{
    //test_cfenv();
    //test_cstdint();
    //test_ctgmath();
    //test_forward_list();
    //test_unordered_map();
    //test_unordered_set();
    //test_ratio();
    test_chrono();

    getchar();
    return 0;
}
