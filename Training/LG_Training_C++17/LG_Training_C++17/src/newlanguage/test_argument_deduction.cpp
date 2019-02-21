#include "test_argument_deduction.h"


namespace test_argument_deduction_
{
    template <typename T = float>
    struct MyContainer {
        T val;
        MyContainer() : val() {}
        MyContainer(T val) : val(val) {}
        // ...
    };
   
    void main()
    {
        MyContainer<int> c1(1); // OK MyContainer<int>
        //MyContainer c2; // OK MyContainer<float>

    }
}

void test_argument_deduction()
{
    test_argument_deduction_::main();
}