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
        for(int i =0; i < 10;i++)
        std::cout << "Calculating. Please, wait...\n";
        for (int i = 2; i<x; ++i) if (x%i == 0) return false;
        return true;
    }
    //create std::future from std::async()
    void test_async()
    {
        // call is_prime(313222313) asynchronously:
        std::future<bool> fut = std::async(std::launch::async , is_prime, 313222313);//create new thread to run is_prime
        //std::future<bool> fut = std::async(std::launch::deferred, is_prime, 313222313);//delay call is_prime until "get,wait" was called
        //std::future<bool> fut = std::async(std::launch::async | std::launch::deferred,is_prime, 313222313);

        for (int i = 0; i < 10; i++)
            std::cout << "Checking whether 313222313 is prime.\n";
        // ...
        std::cout << "checking...\n";
        fut.wait();//Waits for the shared state to be ready.

        std::cout << "wait finish\n";
       
        bool ret = fut.get();      // waits for is_prime to return

        if (ret) std::cout << "It is prime!\n";
        else std::cout << "It is not prime.\n";
    }


    void print_int(std::future<int>& fut) {
        int x = fut.get();
        std::cout << "value: " << x << '\n';
    }

    //A promise is an object that can store a value of type T to be retrieved by 
    //a future object (possibly in another thread), offering a synchronization point.

    void test_promise()
    {
        std::promise<int> prom;                      // create promise

        std::future<int> fut = prom.get_future();    // engagement with future
        std::shared_future<int> shfut = fut.share();

        std::thread th1(print_int, std::ref(fut));  // send future to new thread

        
        std::cout << "set_value: " <<'\n';
        prom.set_value(10);                         // fulfill promise //it unblocks and returns val of future::get
                                                    // (synchronizes with getting the future)
        th1.join();
    }

}

void test_future()
{
    test_future_::test_promise();
    //test_future_::test_async();

}