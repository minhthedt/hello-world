#include "test_others.h"
#include <tuple>
#include <string.h>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////Automatic Type Deduction and decltype////////////////////////////////////////////////////////
namespace test_auto_decltype_
{
    template<class T, class U>
    auto add(T t, U u) { return t + u; } // the return type is the type of operator+(T, U)


    void main()
    {
        //1.0 Automatic Type Deduction  (auto specifier)
        //const char* name = "hello";
        //std::tuple<const char*, double, int, char> bar = std::make_tuple("test", 3.1, 14, 'y');
        auto name = "hello";
        auto bar = std::make_tuple("test", 3.1, 14, 'y');

        //2.0 decltype specifier
        //Inspects the declared type of an entity or the type and value category of an expression.
        int i = 33;
        decltype(i) j = i * 2;
        decltype(auto) k = i * 2;

        decltype(1.2f) a = add(1,2.1f);
        printf("a = %f",a);

    }
}
///////////////////////////////////////////////////////Uniform Initialization Syntax////////////////////////////////////////////////////////

namespace test_uniform_initialization_syntax_
{
    class A
    {
    public:
        int mx;
        double my;
    };

    class B
    {
    public:
        B(int x, double y) : mx{ x }, my{ y } {}

        int mx;
        double my;
    };

    class C
    {
    public:
        C(int x, double y) : mx{ x }, my{ y } {}
        C(const std::initializer_list<int>& v) {
            mx = *(v.begin());
            my = *(v.begin() + 1);
        }

        int mx;
        double my;
    };

    void main()
    {
        int *pi = new int[5]{ 1, 2, 3, 4, 5 };//C++11
        std::vector<int> arr{ 1,2,3,4,5 };      //C++11

        // Aggregate initialization
        A a{ 1, 3.7 };

        // Regular constructor
        B b{ 2, 9.8 };

        // Initializer_list
        C c{ 3, 7 };

        std::cout << a.mx << " " << a.my << std::endl;
        std::cout << b.mx << " " << b.my << std::endl;
        std::cout << c.mx << " " << c.my << std::endl;
    }

}

//https://www.geeksforgeeks.org/explicitly-defaulted-deleted-functions-c-11/
////////////////////////////////////////////////////Deleted and Defaulted Functions///////////////////////////////////////////////
namespace test_default_function_
{
    class A {
    public:

        // A user-defined  
        // parameterized constructor 
        A(int x)
        {
            std::cout << "This is a parameterized constructor";
        }

        // Using the default specifier to instruct 
        // the compiler to create the default  
        // implementation of the constructor. 
        A() = default;

        // Declare the conversion constructor as a  
        // deleted function. Without this step,  
        // even though A(double) isn't defined,  
        // the A(int) would accept any double value  
        // for it's argumentand convert it to an int 
        A(double) = delete;

        void display() = delete;
    };


    void A::display()
    {
        printf("hello world\n");
    };

    void main()
    {
        // executes using defaulted constructor 
        A a;
        //a.display();//disable
        // uses parametrized constructor 
        A x(1);

        // Error, conversion from  
        // double to class A is disabled. 
        //A A2(100.1);
    }

}