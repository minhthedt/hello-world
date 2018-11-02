#include "test_ratio.h"
#include <iostream>
#include <ratio>
//Biểu diễn phân số, gồm tử số + mẫu số (là số nguyên có dấu )
//This header declares the ratio class template and several auxiliary types to operate with them.
//
//A ratio expresses a proportion(such as 1:3, or 1000 : 1) as a set of two compile - time constants
//(its numerator and its denominator).The type itself is used to express the ratio(objects of these types hold no value).
//
//Within the standard library, ratio types are used as template parameters for duration objects(see chrono header).

void test_ratio()
{
    typedef std::ratio<1, 3> one_third;
    typedef std::ratio<2, 4> two_fourths;
    typedef std::ratio<1, 2> one_two;

    std::cout << "one_third= " << one_third::num << "/" << one_third::den << std::endl;//1/3
    std::cout << "two_fourths= " << two_fourths::num << "/" << two_fourths::den << std::endl;//2/4

    typedef std::ratio_add<one_third, two_fourths> sum;
    std::ratio_add<one_third, two_fourths> _sum;
    std::ratio_subtract<one_third, two_fourths> __subtract;
    //ratio_multiply
    //ratio_divide



    std::cout << "_sum= " << _sum.num << "/" << _sum.den;

    std::cout << "sum= " << sum::num << "/" << sum::den;
    std::cout << " (which is: " << (double(sum::num) / sum::den) << ")" << std::endl;

    std::cout << "1 kilogram has " << (std::kilo::num / std::kilo::den) << " grams";
    std::cout << std::endl;

    if (std::ratio_equal<one_two, two_fourths>::value == true)
    {
        std::cout << "1/2 == 2/4 ? " << std::boolalpha;
    }
};