#include "test_array.h"
#include <array>
#include <iostream>

void test_array()
{
    std::array<int, 5> myarray = { 2, 16, 77, 34, 50 };

    myarray[2] = 5;
    std::cout << "myarray contains:";
    for (auto it = myarray.begin(); it != myarray.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}