#include "test_return_type_deduction.h"
//Using an auto return type in C++14, the compiler will attempt to deduce the type for you.
//With lambdas, you can now deduce its return type using auto, which makes returning a deduced reference or rvalue reference possible.


namespace test_return_type_deduction_
{
    //auto f(int i) -> decltype(i)
    //{
    //    return i;
    //}



    template <typename T>
    auto& f(T& t)  {
        return t;
    }




    void main()
    {
        // Returns a reference to a deduced type.
        auto g = [](auto& x) -> auto& { return f(x); };
        int y = 123;
        int& z = g(y); // reference to `y`
    }
}

void test_return_type_deduction()
{
    test_return_type_deduction_::main();
}