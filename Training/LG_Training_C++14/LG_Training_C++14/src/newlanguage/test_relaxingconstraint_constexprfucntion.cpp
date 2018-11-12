#include "test_relaxingconstraint_constexprfucntion.h"
#include <stdio.h>
//Relaxing constraints on constexpr functions

//In C++11, constexpr function bodies could only contain a very limited set of syntaxes, including(but not limited to) : 
//typedefs, usings, and a single return statement.In C++14, the set of allowable syntaxes expands greatly to include the most common syntax such as 
//if statements, multiple returns, loops, etc.


namespace test_relaxingconstraint_constexprfucntion_
{
    //multiple returns C++14, C++11 allow only one return;
    constexpr int factorial(int n) {
        if (n <= 1) {
            return 1;
        }
        else {
            return n * factorial(n - 1);
        }
    }

    void main()
    {
        int a = factorial(5); // == 120
        printf("factorial(5) = %d",a);
    }
}

void test_relaxingconstraint_constexprfucntion()
{
    test_relaxingconstraint_constexprfucntion_::main();
}