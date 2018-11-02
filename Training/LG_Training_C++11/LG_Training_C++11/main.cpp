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
extern void test_random();
extern void test_regex();
extern void test_system_error();
extern void test_tuple();
extern void test_typeindex();
extern void test_type_traits();

extern void test_automic();

int main(char argn, char** argv)
{
    //test_cfenv();
    //test_cstdint();
    //test_ctgmath();
    //test_forward_list();
    //test_unordered_map();
    //test_unordered_set();
    //test_ratio();
    //test_chrono();
    //test_random();
    //test_regex();
    //test_system_error();
    //test_tuple();
    //test_typeindex();
    //test_type_traits();

    test_automic();


    getchar();
    return 0;
}
