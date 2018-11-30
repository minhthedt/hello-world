#include "test_Rvalue.h"
#include <iostream>
#include <string>

namespace test_Rvalue_
{

    class A
    {
        
    public:
        int* ptr;

        A()
        {
            printf("A constructor 1 \n");
        }
        A(int val)
        {
            printf("A constructor 2\n");
            ptr = new int(val);
        }

        A(A& other)
        {
            this->ptr = other.ptr;
            printf("A constructor 3 \n");
        }

        A& operator=(A& other)
        {
            printf("A operator 1 \n");
            this->ptr = other.ptr;
        }

        A(A&& other)
        {
            this->ptr  = other.ptr;
            other.ptr = nullptr;
            printf("A constructor 3 \n");
        }

        ~A()
        {
            //if (ptr) delete ptr;
            //ptr = nullptr;
        }
        
    };

    //A Handle(A a)
    //{
    //    printf("Handle 1 \n");
    //    return a;
    //}

    A Handle(A& a)
    {
        printf("Handle 2 \n");
        return a;
    }

    A Handle(A&& a)
    {
        printf("Handle 3 \n");
        return a;
    }

    //A c(5);
    void main()
    {
        A a(3);
        //A b = Handle(a);
        //A c = Handle(std::move(a));
        A d= Handle(Handle(a));

    }
}

void test_Rvalue()
{
    test_Rvalue_::main();
}