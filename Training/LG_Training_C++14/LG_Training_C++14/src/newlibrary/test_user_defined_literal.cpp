#include "test_user_defined_literal.h"
#include <iostream>
#include <string>
#include <chrono>


namespace test_user_defined_literal_
{
    class Student
    {
        int age;
    public:
        Student(unsigned long long a)
        {
            age = a;
        }

        void display()
        {
            std::cout << "age = " << age << std::endl;
        }
    };
    // used as conversion
    constexpr long double operator"" _deg(long double deg)
    {
        return deg * 3.141592 / 180;
    }

    //expected char,w_chart,char16_t,char32_t,unsigned long long
    long double operator"" _days(long double d)//pointer to no-const type is not allowed
    {
        return 24 * 60* 60 * d ;
    }

    long double operator"" _hours(long double d)//pointer to no-const type is not allowed
    {
        return 60 * 60 * d;
    }

    long double operator"" _minutes(long double d)//pointer to no-const type is not allowed
    {
        return 60 * d;
    }

    long double operator"" _seconds(long double d)//pointer to no-const type is not allowed
    {
        return 60 * d;
    }

    Student operator"" _st(unsigned long long d )
    {
        return Student(d);
    }


    //C++11
    void test()
    {
        double time = 1.0_days + 1.0_hours + 1.0_minutes + 1.0_seconds;
        std::cout << "time = " <<time <<  " seconds" << '\n';//86400

        Student st = 3_st;
        st.display();
    }

    void main()
    {
        test();
        //C++14 user-defined literals for standard library types (chrono and basic_string)
        using namespace std::chrono_literals;

        //auto day = std::chrono::hours(24);//c++11
        auto day = 24h;//c++14
        day.count(); // == 24
        std::chrono::duration_cast<std::chrono::minutes>(day).count(); // == 1440
    }
}


void test_user_defined_literal()
{
    test_user_defined_literal_::main();
}
