#include "test_exception.h"
#include <stdio.h>
#include <iostream> //exception
#include <string>
#include <exception> //C++ Standard Exceptions
#include <memory>
namespace test_exception_
{
    class MyClass
    {
    public:
        ~MyClass()
        {
            printf("Destructor ~A \n");
        }
    };

    class MyException
    {
    public:
        std::string msg;
        MyException(const char* m)
        {
            msg = m;
        }
    };

    class MyExceptionA : public MyException
    {
    public:
        MyExceptionA(const char* m) : MyException(m)
        {
            msg += " A";
        }
    };

    //Define New Exceptions
    //Here, what() is a public method provided by exception class and it has been overridden
    //by all the child exception classes.This returns the cause of an exception.
    struct MyExceptionB : public std::exception {
        const char * what() const throw () {
            return "C++ Exception";
        }
    };

    double division(int a, int b) {
        if (b == 0) {
            //throw "Division by zero condition!";
            throw MyExceptionA("Division by zero condition!");
        }
        return (a / b);
    }

    MyClass* f1()
    {
        MyClass* p = new MyClass();
        //do something - maybe throw an exception
        throw "i want to throw";
        return p;
    }

    MyClass* f2()
    {
        std::unique_ptr<MyClass> p(new MyClass);
        //do something - maybe throw an exception
        throw "i want to throw";
        return p.release();
    }

    std::unique_ptr<MyClass> f3()
    {
        std::unique_ptr<MyClass> p(new MyClass);
        //do something - maybe throw an exception
        throw "i want to throw";
        return p;
    }

    //void main()
    //{
    //    MyClass* a = nullptr;
    //    try
    //    {
    //        a = f1();
    //    }
    //    catch (const char* str)
    //    {
    //        printf("%s\n", str);//i want to throw
    //    }

    //    printf("a = 0x%x", a);// a was not setted value
    //    //leak memory , dont call destructor of A 
    //}

    void main()
    {
        //int x = 50;
        //int y = 0;
        //double z = 0;

        //try {
        //    
        //    z = division(x, y);
        //    std::cout << z << std::endl;//can not run this code if throw
        //}
        //catch (const char* msg) { //throw "Division by zero condition!";
        //    std::cerr << msg << std::endl;
        //}
        //catch (const MyException& e) { // throw MyExceptionA("Division by zero condition!");
        //    std::cerr << e.msg; //Division by zero condition! A
        //}

        //printf("\nz = %d\n",z);

        //try
        //{
        //    int* a = new int;
        //    delete a;
        //    //delete a;//delete 2 times -> CRASH: can not throw exception
        //}
        //catch (const std::exception& e) 
        //{
        //    std::cout << e.what() << std::endl;
        //}

        //MyClass* a = nullptr;
        //try
        //{
        //    a = f2();//leak memory , dont call destructor of A 
        //}
        //catch (const char* str)
        //{
        //    printf("%s\n",str);
        //}

        //printf("a = 0x%x",a);

        //try
        //{
        //    a = f2();//OK
        //}
        //catch (const char* str)
        //{
        //    printf("%s\n", str);
        //}
       
        try
        {
            std::unique_ptr<MyClass> q = f3();
            
        }
        catch (const char* str)
        {
            printf("%s\n", str);
        }

    }

}

void test_exception()
{
    test_exception_::main();
}