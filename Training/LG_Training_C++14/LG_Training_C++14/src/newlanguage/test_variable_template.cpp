#include "test_variable_template.h"


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

    }
}

void test_variable_template()
{
    test_variable_template_::main();
}