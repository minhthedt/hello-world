#include "test_others.h"
#include <tuple>
#include <string.h>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <thread>
#include <mutex>

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

  /*  template <typename T>
    class myShare
    {
    public:
        int* count = nullptr;
        T* ptr;

        myShare():count(nullptr),ptr(nullptr)
        {
        }

        myShare(T* p)
        {
            if (!count)
            {
                count = new int;
                *count = 0;
            }
            *count++;
            ptr = p;
        }

        myShare(myShare<T> share)
        {
            ptr = share.ptr;
            count = share.count;
            *count++;
        }

        ~myShare()
        {
            *count--;
            if (count == 0) delete ptr;
            ptr = nullptr;
        }
    };

*/


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

        std::vector<int> v = { 3, 1, 4 };
        for (auto it = std::begin(v); it != std::end(v); it++)
        {
            // Do something
        }
        //int x3{ 5.0 };
        std::initializer_list<int> mylist;
        //mylist = { 10, 20, 30.3 };
    }

}

/////////////////////////////Override and final////////////////
namespace test_override_final_
{
    class A
    {
    public:
        virtual void f(int) { printf("A::f \n"); }
    };

    class B : public A
    {
    public:
        virtual void f(int) override { printf("B::f \n"); }
    };

    class C : public B
    {
    public:
        virtual void f(int) override final { printf("C::f \n"); }
    };

    //class D : public C
    //{
    //public:
    //    virtual void f(int) override  { printf("C::f \n"); }
    //};

}

//test lambda
namespace test_lambda_
{

    void main()
    {
        int a = 2, b = 3;
        bool status = false;
        auto add = [&status](int a, int b) -> int
        {
            status = true;
            return a + b;
        };
        int sum = add(a, b);
        //sum = 5, status = true

        int sum2 = [&status](int a_, int b_)
        {
            status = true;
            return a_ + b_;
        }(a,b);
        //sum2 = 5, status = true
    }
}
//test share_ptr

namespace test_smart_pointer_
{
    class A
    {
    public:
        int a;
        A() :a(0) {};
        A(int in) : a(in) { a = in; };
        void print() { printf("A::printf a = %d\n",a); }
    };

    void test_shared_ptr()
    {

        {
            std::shared_ptr<A> p(new A[2]{ 1,2 }, [](A* arr)
            {
                delete[] arr;
            }
            );


            A* ptr = p.get();
            ptr->print();//A::printf a = 1
            ptr++;
            ptr->print();//A::printf a = 2
        }

        {
            std::shared_ptr<A[]> p(new A[2]{ 1,2 }, [](A* arr)
            {
                delete[] arr;
            }
            );

            p[0].print();//A::printf a = 1
            p[1].print();//A::printf a = 2

        }
    }

    void test_weak_ptr()
    {
        auto sp = std::make_shared<A>(42);
        std::weak_ptr<A> wp = sp;
        int count = wp.use_count();
        std::shared_ptr<A> bb = wp.lock();
        printf("wp.use_count() = %d \n", wp.use_count());
        sp.reset();
        printf("After sp.reset() wp.use_count() = %d \n", wp.use_count());
    }

    std::unique_ptr<A> pass_through(std::unique_ptr<A> p)
    {
        p->a = 6;
        return p;
    }

    void test_unique_ptr()
    {
        //std::unique_ptr<A> up = std::make_unique<A>();
        std::unique_ptr<A> up (new A(12));
        up->print();
        //std::unique_ptr<A> b = up;//ERROR
        std::unique_ptr<A> b = std::move(up);//OK
        std::unique_ptr<A> c = pass_through(std::move(b));
        std::shared_ptr<A> sp(c.release());
        sp->print();
        if (!b) printf("b == nullptr\n");
        if (!c) printf("c == nullptr\n");
    }
 
    void main()
    {
        test_shared_ptr();
        //test_weak_ptr();
        //test_unique_ptr();
       
    }
}


void test_smart_pointer()
{
    test_smart_pointer_::main();
}

/////////////////////static_assert and type traits/////////////////////
namespace test_static_assert_
{
    template<typename T, size_t size>
    class Vector
    {
        public:
            //static_assert(size > 3,"size must be lager than 3");
            //static_assert(std::is_integral<T>::value, "T must be integer");
            T m_points[size];
    };

    void main()
    {
        Vector<int, 10> v1;
        Vector<int, 2> v2;//size must be lager than 3
        Vector<float, 10> v3;//T must be integer
    }
}

void test_static_assert()
{
    test_static_assert_::main();
}


    #define NUMBER_LOOP 1000000
    signed long long x = 0;
    std::mutex mtx;           // mutex for critical section

    void add()
    {
        for (int i = 0; i < NUMBER_LOOP; i++)
        {
            mtx.lock();
            x++;
            mtx.unlock();
        };

    }
    void sub()
    {
        for (int i = 0; i < NUMBER_LOOP; i++)
        {
            mtx.lock();
            x--;
            mtx.unlock();
        };
    }


   
    //#define NUMBER_LOOP 1000000
    //int x = 0;
    //// std::atomic<signed long long>  x = 0;

    //void add()
    //{
    //    for (int i = 0; i < NUMBER_LOOP; i++)
    //    {
    //        x++;
    //    };

    //}
    //void sub()
    //{
    //    for (int i = 0; i < NUMBER_LOOP; i++)
    //    {
    //        x--;
    //    };
    //}


    //void main()
    //{
    //    std::vector<std::thread> theads;
    //    for (int i = 0; i < 10; i++)
    //    {
    //        theads.push_back(std::thread(add));
    //        theads.push_back(std::thread(sub));
    //    }

    //    for (int i = 0; i < theads.size(); i++)
    //    {
    //        theads[i].join();
    //    }

    //    signed long long a = x;
    //    printf("x = %lld\n", a);
    //}