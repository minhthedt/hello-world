#include "test_variable_template.h"
#include <iostream>
#include <string>

namespace  test_variable_template_
{
    template<class T>
    constexpr T pi = T(3.1415926535897932385L);  // variable template

    template<class T>
    T circular_area(T r) // function template
    {
        return pi<T> * r * r; // pi<T> is a variable template instantiation
    }

    void main()
    {
        auto val1 = circular_area<float>(3.5f);//38.4845
        auto val2 = circular_area<int>(3.5f);//27
        std::cout << "val1 = " << val1 << "\nval2 = " << val2 << std::endl;
    }
}

void test_variable_template()
{
    test_variable_template_::main();
}