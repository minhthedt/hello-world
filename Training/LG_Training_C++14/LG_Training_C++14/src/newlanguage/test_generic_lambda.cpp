#include "test_generic_lambda.h"
#include <iostream>
#include <string>
#include <functional>
#include <type_traits>
//C++14 now allows the auto type-specifier in the parameter list, enabling polymorphic lambda


struct lambda1
{
    template<typename A, typename B>
    auto operator()(A a, B b) const -> decltype(a * b)
    {
        return a * b;
    }
};


void test_generic_lambda()
{
    auto identity = [](auto x) { return x; };
    int foo1 = identity(3); // == 3
    auto foo2 = identity(3.3f); // == 3.3
    std::string foo3 = identity("foo"); // == "foo"
    std::cout << foo1 << std::endl;
    std::cout << foo2 << std::endl;
    std::cout << foo3 << std::endl;

    //C++11
    std::function<int(int,int)> lambda1 = [](int a, int b) -> int
    { return a * b; };

    //C++11
    auto lambda2 = [](int a, int b) -> decltype(a*b)
    { return a * b; };

    //C++14
    auto lambda3 = [](auto a, auto b) -> int
    { return a * b; };

    //C++14
    auto lambda4 = [](auto a, auto b) -> auto
    { return a * b; };

    //C++14
    auto lambda5 = [](auto a, auto b) 
    { return a * b; };


    std::cout << "lambda1 = " << lambda1(1, 3) << " lambda1 = " << lambda1(1.1, 3.3) << std::endl;
    std::cout << "lambda3 = " << lambda3(1, 3) << " lambda3 = " << lambda3(1.1, 3.3) << std::endl;
    std::cout << "lambda5 = " << lambda5(1, 3) << " lambda5 = " << lambda5(1.1, 3.3) << std::endl;
}