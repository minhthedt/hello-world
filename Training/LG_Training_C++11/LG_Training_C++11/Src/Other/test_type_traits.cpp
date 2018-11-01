#include "test_type_traits.h"
#include <iostream>
#include <type_traits>
//This header defines a series of classes to obtain type information on compile-time.
//Kiểm tra thuộc tính của 1 class: class là abstract, có copy constructor, có đa hình ....
struct A {
    virtual void fn() = 0;
};
struct B 
{ 
    void fn() {} 
    B& operator= (const A&) { return *this; }
};
struct C 
{ 
    int x; 
};


void test_type_traits()
{
    std::cout << std::boolalpha;
    std::cout << "is_empty:" << std::endl;//is_empty:
    std::cout << "int: " << std::is_empty<int>::value << std::endl; //int : false
    std::cout << "A: " << std::is_empty<A>::value << std::endl;//A : true
    std::cout << "B: " << std::is_empty<B>::value << std::endl;//B : true
    std::cout << "C: " << std::is_empty<C>::value << std::endl;//C : false

    std::cout << "\nis_assignable:" << std::endl;
    std::cout << "A=B: " << std::is_assignable<A, B>::value << std::endl;//A=B: false
    std::cout << "B=A: " << std::is_assignable<B, A>::value << std::endl;//B=A: true

    std::cout << "\nis_abstract:" << std::endl;
    std::cout << "A: " << std::is_abstract<A>::value << std::endl;//true
    std::cout << "B: " << std::is_abstract<B>::value << std::endl;//false
    std::cout << "C: " << std::is_abstract<C>::value << std::endl;//false
   
    
    
    
}