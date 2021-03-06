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

extern void test_thread();
extern void test_automic();
extern void test_automic_flag();
extern void test_mutex();
extern void test_future();
extern void test_condition_variable();

extern void test_others();
extern void test_exception();
extern void test_smart_pointer();

extern void test_static_assert();

#include <map>
#include <functional>
#include <iostream>
#include <string>
using namespace std;
struct ByLength : public std::binary_function<string, string, bool>
{
    bool operator()(const string& lhs, const string& rhs) const
{
    return lhs.length() < rhs.length();
}
};

void Amain()
{
    typedef map<string, string, ByLength> lenmap;
    lenmap mymap;

    mymap["one"] = "one";
    mymap["a"] = "a";
    mymap["fewbahr"] = "foobar";

    for (lenmap::const_iterator it = mymap.begin(), end = mymap.end(); it != end; ++it)
        cout << it->first << "\n";
}


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

    //test_thread();
    //test_automic();
    //test_automic_flag();
    //test_mutex();
    //test_future();
    test_condition_variable();

    //test_others();
    //test_exception();
    //test_smart_pointer();

    //test_static_assert();

    getchar();
    return 0;
}
