#include "test_automic.h"
#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // std::thread, std::this_thread::yield
#include <vector>         // std::vector
#include <mutex>
#include <chrono>

//template <class T> struct atomic;
//Objects of atomic types contain a value of a particular type(T).
//
//The main characteristic of atomic objects is that access to this contained value from different threads cannot cause data races
//(i.e., doing that is well - defined behavior, with accesses properly sequenced).Generally, for all other objects, the possibility of causing a data race 
//for accessing the same object concurrently qualifies the operation as undefined behavior.

//Functions for atomic objects (C-style)
//atomic_init : Initialize atomic object
//atomic_store : Modify contained value
//atomic_load  : Read contained value 
//atomic_exchange : Read and modify contained value
//atomic_fetch_add : Add to contained value //The entire operation is atomic
//atomic_fetch_sub
//atomic_fetch_and
//atomic_fetch_or
//atomic_fetch_xor

//
//atomic_flag_test_and_set :Test and set atomic flag
//atomic_flag_clear        :Clear atomic flag

namespace test_automic_
{
    #define USE_AUTOMIC 1

    #if USE_AUTOMIC
    std::atomic<signed long long>  x = 0;
    #else
    signed long long x = 0;
    #endif

    #define NUMBER_LOOP 1000000

    void add()
    {
        for (int i = 0; i < NUMBER_LOOP; i++)
        {
            //std::atomic::operator++
            x++;
            //int m = x.fetch_add(1);
            //std::atomic_fetch_add(&x,1);//C-style
        };
    
    }
    void sub()
    {
        for (int i = 0; i < NUMBER_LOOP; i++)
        {
            //std::atomic::operator--
            x--;
            //int m = x.fetch_add(-1);
            //std::atomic_fetch_add(&x,-1);//C-style
        };
    }

    class A
    {
    public:
        int m,n;
        
        void display() 
        {
             printf("m = %d n = %d\n", m,n);
        }

    };

    class B 
    {
        int a;
        char str[4];
        B(int m_, int n_)  {};//not trivially copyable
        virtual void display() //not trivially copyable
        {
            printf("a = d\n", a);
        }
    };

    void main()
    {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> theads;
        for (int i = 0; i < 10; i++)
        {
            theads.push_back(std::thread(add));
        }

        for (int i = 0; i < 10; i++)
        {
            theads.push_back(std::thread(sub));
        }


        for (int i = 0; i < theads.size(); i++)
        {
            theads[i].join();
        }

        signed long long a = x;
        //signed long long a = std::atomic_load(&x);
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    #if USE_AUTOMIC
        printf("USE_AUTOMIC: x = %lld\n",a);
        std::cout << "elapsed time " << time_span.count() << " seconds." << std::endl;
    #else
        printf("don't USE_AUTOMIC: x = %lld\n", a);
        std::cout << "elapsed time " << time_span.count() << " seconds." << std::endl;
    #endif

        std::atomic<A> aa;// chưa tìm thấy trường hợp nào dùng atomic kiểu class ???
        //https://en.cppreference.com/w/cpp/types/is_trivially_copyable
        //std::atomic<B> bb;//compile Error	C2338	atomic<T> requires T to be trivially copyable
        printf("aa.is_lock_free() = %s\n", aa.is_lock_free() ? "true" : "false");//true
    }

}

void test_automic()
{
    test_automic_::main();
}

namespace test_automic_flag_
{
    signed long long x = 0;
    std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
    //std::atomic<bool> lock_stream = false;
    
  #define NUMBER_LOOP 1000000

    void add()
    {
        for (int i = 0; i < NUMBER_LOOP; i++)
        {
            while (lock_stream.test_and_set()) {}//bad performance
            //while (lock_stream.exchange(true)) {}
            x++;
            lock_stream.clear();
            //lock_stream = false;
        };

    }
    void sub()
    {
        for (int i = 0; i < NUMBER_LOOP; i++)
        {
            while (lock_stream.test_and_set()) {}
            //while (lock_stream.exchange(true)) {}
            x--;
            lock_stream.clear();
            //lock_stream = false;
        };
    }

    

    void main()
    {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> theads;
        for (int i = 0; i < 10; i++)
        {
            theads.push_back(std::thread(add));
        }

        for (int i = 0; i < 10; i++)
        {
            theads.push_back(std::thread(sub));
        }


        for (int i = 0; i < theads.size(); i++)
        {
            theads[i].join();
        }

        signed long long a = x;
        //signed long long a = std::atomic_load(&x);
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

        printf("USE_AUTOMIC_FLAG: x = %lld\n", a);
        std::cout << "elapsed time " << time_span.count() << " seconds." << std::endl;
    }
}

void test_automic_flag()
{
    test_automic_flag_::main();
}