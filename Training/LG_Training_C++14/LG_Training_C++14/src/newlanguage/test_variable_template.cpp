#include "test_variable_template.h"
#include <iostream>
#include <string>
#include <math.h>

namespace  test_variable_template_
{
    template<class T>
    T pi = T(3.1415926535897932385L);  // variable template

    template<class T>
    T circular_area(T r) // function template
    {
        return pi<T> * r * r; // pi<T> is a variable template instantiation
    }

    template <int N> struct Factorial {
        static const int result = N * Factorial<N - 1>::result;
    };

    template <> struct Factorial<0> {
        static const int result = 1;
    };

    struct ST
    {
        long double d;
        ST(long double d_):d(d_)
        {

        }
    };




    template <typename T, int N>
    struct hermitian_matrix
    {

    };



    using namespace std::literals;
    struct matrix_constants
    {
        template<class T>
        using pauli = hermitian_matrix<T, 2>; // alias template

        template<class T> // static data member template
        static constexpr pauli<T> sigmaX = { { 0, 1 },{ 1, 0 } };

        template<class T>
        static constexpr pauli<T> sigmaY = { { 0, -1i },{ 1i, 0 } };

        template<class T>
        static constexpr pauli<T> sigmaZ  = { { 1, 0 },{ 0, -1 } };

       
    };

    template <typename T>
    struct PI {
        static constexpr T pi = T(3.1415926535897932385);
    };

    void main()
    {
        printf("%d\n", PI<int>::pi);
        printf("%lf\n", PI<double>::pi);

        printf("PI: %d, area: %d\n", pi<int>);
        printf("PI: %lf, area: %lf\n", pi<double>);
        pi<double> = 2.3;
        printf("PI: %lf, \n", pi<double>);

        //int size = sizeof(matrix_constants);
        //auto aa = matrix_constants::pi<ST>;
        auto val1 = circular_area<float>(3.5f);//38.4845
        auto val2 = circular_area<int>(3.5f);//27
        std::cout << "val1 = " << val1 << "\nval2 = " << val2 << std::endl;
        std::cout << Factorial<5>::result << "\n";
    }
}

void test_variable_template()
{
    test_variable_template_::main();
}