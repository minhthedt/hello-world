#include "test_initializer_list.h"
#include <iostream>          // std::cout
#include <initializer_list>  // std::initializer_list
#include <string>            // std::string
#include <sstream>           // std::stringstream


struct myclass {
    std::string str;
    myclass(std::initializer_list<int> args) {
        std::stringstream ss;
        std::initializer_list<int>::iterator it;  // same as: const int* it
        for (it = args.begin(); it != args.end(); ++it) ss << ' ' << *it;
        str = ss.str();
    }
};

void test_initializer_list()
{
    std::initializer_list<int> mylist;
    mylist = { 10, 20, 30 };
    std::cout << "mylist contains:";
    for (int x : mylist) std::cout << ' ' << x;
    std::cout << '\n';

    myclass myobject { 10, 20, 30 };//Initializer-list constructors take precedence over other constructors when the initializer-list constructor syntax is used
    std::cout << "myobject contains:" << myobject.str << '\n';
}