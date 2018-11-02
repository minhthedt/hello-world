#include "test_automic.h"
#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // std::thread, std::this_thread::yield
#include <vector>         // std::vector


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
//atomic_fetch_add : Add to contained value
//atomic_fetch_sub
//atomic_fetch_and
//atomic_fetch_or
//atomic_fetch_xor

//
//atomic_flag_test_and_set :Test and set atomic flag
//atomic_flag_clear        :Clear atomic flag

//std::atomic<bool> ready(false);
bool ready = false;
std::atomic_flag winner = ATOMIC_FLAG_INIT;
bool global = false;


void count1m(int id) {
    while (!ready) 
    { 
        std::this_thread::yield(); 
    }      // wait for the ready signal
    for (volatile int i = 0; i<100; ++i) 
    {
        std::cout << "thread #" << id << "i =" << i << std::endl;
    }          // go!, count to 1 million
    if (!winner.test_and_set()) 
    { 
        std::cout << "thread #" << id << " won!\n"; 
    }
    //if (!global)
    //{
    //    global = true;
    //     std::cout << "thread #" << id << " won!\n"; 
    //}
};

unsigned long long foo = 0;
void set_foo(int id) {
    printf("thread %d:\n", id);
    foo++;
    unsigned long long x = foo;
    printf("thread %d: x = %lld\n", id,x);
}

void print_foo() 
{
    int t = foo;
   
}

void test_automic()
{
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i = 1; i <= 1000; ++i) threads.push_back(std::thread(set_foo,i));
    ready = true;
    for (auto& th : threads) th.join();

}