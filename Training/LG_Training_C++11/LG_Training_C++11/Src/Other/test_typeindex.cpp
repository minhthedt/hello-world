#include "test_typeindex.h"
// type_index example
#include <iostream>       // std::cout
#include <typeinfo>       // operator typeid
#include <typeindex>      // std::type_index
#include <unordered_map>  // std::unordered_map
#include <string>         // std::string
//Class that wraps a type_info object so that it can be copied(copy - constructed and copy - assigned)
//and /or be used used as index by means of a standard hash function.

struct C {  void Member() {} };
struct B : public C {};

struct Base {};
struct Derived : Base {};
struct Poly_Base { virtual void Member() {} };
struct Poly_Derived : Poly_Base {};
typedef int my_int_type;

void test_typeindex()
{
    std::cout << std::boolalpha;

    std::unordered_map<std::type_index, std::string> mytypes;
   

    std::tuple<int, int> dataA;
    std::tuple<int, int> dataB;
    if(typeid(dataA) == typeid(dataB))
    std::cout << "name: " << typeid(dataA).name() << "hashcode: " << typeid(dataA).hash_code() << '\n';
    //name: class std::tuple<int, int> hashcode: 2364305075570905573

    mytypes[typeid(int)] = "Integer type";
    mytypes[typeid(double)] = "Floating-point type";
    mytypes[typeid(C)] = "Custom class named C";
    mytypes[typeid(B)] = "Custom class named B";

    std::cout << "int: " << mytypes[typeid(int)] << '\n';
    std::cout << "double: " << mytypes[typeid(double)] << '\n';
    std::cout << "C: " << mytypes[typeid(C)] << '\n';

    C* b = new B();
    std::cout << "B: " << typeid(*b).name() << '\n';//Hiển thị loại khi được khai báo (C*)
    std::cout << "base vs *derived " << (typeid(C) == typeid(*b)) << "\n\n";//true >>>>>>>>>>>>>>>>>>>>
    //int: Integer type
    //double : Floating - point type
    //C : Custom class named C
    //B: struct B

   

    // fundamental types:
    std::cout << "int vs my_int_type: ";
    std::cout << (typeid(int) == typeid(my_int_type)) << '\n';

    // class types:
    std::cout << "Base vs Derived: ";
    std::cout << (typeid(Base) == typeid(Derived)) << '\n';

    // non-polymorphic object:
    Base* pbase = new Derived;

    std::cout << "Base vs *pbase: ";
    std::cout << (typeid(Base) == typeid(*pbase)) << '\n';

    // polymorphic object:
    Poly_Base* ppolybase = new Poly_Derived;

    //=> nếu virtual đa hình thì check sẽ khác
    std::cout << "Poly_Base vs *ppolybase: ";
    std::cout << (typeid(Poly_Base) == typeid(*ppolybase)) << '\n';//false >>>>>>>>>>>>>>>>>>>>
}