#include "test_constexp.h"
#include <chrono>
#include <ratio>
#include <iostream>
#include <ctime>
//https://github.com/AnthonyCalandra/modern-cpp-features
//Understanding constexpr specifier in C++
//constexpr is a feature added in C++ 11. The main idea is performance improvement of programs by doing computations at compile time rather than 
//run time.Note that once a program is compiled and finalized be developer, it is run multiple times by users.The idea is to spend time in compilation and save time at run time(similar to template metaprogramming)


constexpr long int fib(int n)
{
    return (n <= 1) ? n : fib(n - 1) + fib(n - 2);
}


template <int n>
struct constN
{
    constN() { std::cout << n << '\n'; }
};

auto identity = [](int x) { return x; };
int three = identity(3); // == 3

void test_constexp()
{
    using namespace std::chrono;
    system_clock::time_point t1 = system_clock::now();

    const long int res = fib(45);
    //long int res = fib(45);
    std::cout << "res = " << three << std::endl;
   
    //constN<fib(4)> out1;

    system_clock::time_point t2 = system_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "system_clock : It took me " << time_span.count() << " seconds.\nres = " << res << std::endl;
}