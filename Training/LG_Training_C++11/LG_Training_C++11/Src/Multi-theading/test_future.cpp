#include "test_future.h"
#include <iostream>
#include <future>
#include <thread>

//https://www.justsoftwaresolutions.co.uk/threading/multithreading-in-c++0x-part-8-futures-and-promises.html
//In this installment we'll take a look at the "futures" mechanism from C++0x. Futures are a high level mechanism for 
//passing a value between threads, and allow a thread to wait for a result to be available without having to manage the locks directly.


namespace test_future_
{

    // a non-optimized way of checking for prime numbers:
    bool is_prime(int x) {
        for (int i = 2; i<x; ++i) if (x%i == 0) return false;
        return true;
    }

    //create std::future from std::async()
    void test_async()
    {
        // call function asynchronously:
        std::future<bool> fut = std::async(is_prime, 444444443);

        // do something while waiting for function to set future:
        std::cout << "checking, please wait";
        std::chrono::milliseconds span(100);
        while (fut.wait_for(span) == std::future_status::timeout)
            std::cout << '.' << std::flush;

        bool x = fut.get();     // retrieve return value

        std::cout << "\n444444443 " << (x ? "is" : "is not") << " prime.\n";

        //checking, please wait........................
        //444444443 is prime.

    }

    void print_int(std::future<int>& fut) 
    {
        int x = fut.get();
        std::cout << "value: " << x << '\n';
    }

    void print_intA(std::promise<int>& prom)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        prom.set_value(10);
      
    }

    void print_intB(std::shared_future<int> fut)
    {
        int x = fut.get();
        std::cout << "value: " << x << '\n';

    }

    //A promise is an object that can store a value of type T to be retrieved by 
    //a future object (possibly in another thread), offering a synchronization point.

    void test_promise()
    {
        std::promise<int> prom;                      // create promise

        std::future<int> fut = prom.get_future();    // engagement with future

        std::thread th1(print_int, std::ref(fut));  // send future to new thread
        //std::thread th2(print_int, std::ref(fut));  // ERROR

        prom.set_value(10);                         // fulfill promise
                                                    // (synchronizes with getting the future)
        th1.join();
    }

    void test_promiseA()
    {
        std::promise<int> prom;                      // create promise

        std::future<int> fut = prom.get_future();    // engagement with future

        std::thread th1(print_intA, std::ref(prom));  // send future to new thread
                                                    //std::thread th2(print_int, std::ref(fut));  // ERROR

        //std::future<int> fut1 = prom.get_future();//ERROR: only one future was retrieved
        int x = fut.get();                        // fulfill promise
                                                    // (synchronizes with getting the future)
        printf("x = %d",x);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        th1.join();
        
    }

    void test_promiseB()
    {
        std::promise<int> prom;                      // create promise

        std::shared_future<int> fut = prom.get_future();    // engagement with future
        std::shared_future<int> fut1 = fut;

        std::thread th1(print_intB, fut);  // send future to new thread
        std::thread th2(print_intB, fut1);  // OK
        th1.detach();
        th2.detach();

        prom.set_value(10);                         // fulfill promise
                                                    // (synchronizes with getting the future)

        std::this_thread::sleep_for(std::chrono::seconds(2));
       

    }


    void test_promiseC()
    {
        std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
        std::shared_future<void> ready_future(ready_promise.get_future());

        std::chrono::time_point<std::chrono::high_resolution_clock> start;

        auto fun1 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
        {
            //t1_ready_promise.set_value();
            ready_future.wait(); // waits for the signal from main()
            return std::chrono::high_resolution_clock::now() - start;
        };


        auto fun2 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
        {
            //t2_ready_promise.set_value();
            ready_future.wait(); // waits for the signal from main()
            return std::chrono::high_resolution_clock::now() - start;
        };

        auto fut1 = t1_ready_promise.get_future();
        auto fut2 = t2_ready_promise.get_future();

        auto result1 = std::async(std::launch::async, fun1);
        auto result2 = std::async(std::launch::async, fun2);

        // wait for the threads to become ready
        //fut1.wait();
        //fut2.wait();

        // the threads are ready, start the clock
        start = std::chrono::high_resolution_clock::now();

        // signal the threads to go
        ready_promise.set_value();

        std::cout << "Thread 1 received the signal "
            << result1.get().count() << " ms after start\n"
            << "Thread 2 received the signal "
            << result2.get().count() << " ms after start\n";
    }

}

void test_future()
{
    //test_future_::test_promiseC();
    test_future_::test_promiseB();
    //test_future_::test_promiseA();
    //test_future_::test_promise();
    //test_future_::test_async();

}