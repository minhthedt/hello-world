#include "test_tuple.h"
//Tuples are objects that pack elements of -possibly- different types together in a single object, 
//just like pair objects do for pairs of elements, but generalized for any number of elements.
//A tuple is an object capable to hold a collection of elements. Each element can be of a different type.
#include <iostream>     // std::cout
#include <tuple>        // std::tuple, std::get, std::tie, std::ignore

void test_tuple()
{
    std::tuple<int, char> foo(10, 'x');

    //auto bar = std::make_tuple("test", 3.1, 14, 'y');
    std::tuple<const char*,double,int,char> bar  = std::make_tuple("test", 3.1, 14, 'y');

    auto myauto = std::tuple_cat(bar, std::tuple<int, char>(foo));//nối 2 tuple theo thứ tự
    std::cout << "myauto contains: " << '\n';
    std::cout << std::get<0>(myauto) << '\n';
    std::cout << std::get<1>(myauto) << '\n';
    std::cout << std::get<2>(myauto) << '\n';
    std::cout << std::get<3>(myauto) << '\n';
    //myauto contains: "test", 3.1, 14, 'y',10, 'x'

    std::get<2>(bar) = 100;                                   // access element

    int myint; char mychar;

    std::tie(myint, mychar) = foo;                            // unpack elements, set value for myint,mychar
    std::tie(std::ignore, std::ignore, myint, mychar) = bar;  // unpack (with ignore), set value for myint,mychar

    mychar = std::get<3>(bar);//Returns a reference to the 3th element of tuple tpl.

    std::get<0>(foo) = std::get<2>(bar);
    std::get<1>(foo) = mychar;

    std::cout << "foo contains: ";
    std::cout << std::get<0>(foo) << ' ';
    std::cout << std::get<1>(foo) << '\n';
    //foo contains: 100 y
}