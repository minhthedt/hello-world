#include "test_thread.h"
#include <thread>
#include <iostream>

namespace test_thread_
{
#define NUMBER_LOOP 10
    void foo()
    {
        for(int i =0; i < NUMBER_LOOP; i ++ )
                   printf("i am foo %d \n",i);
    }   

    void bar(int id)
    {
        for (int i = 0; i < NUMBER_LOOP; i++)
            printf("i am bar %d id = %d\n", i,id);
    }

    void main()
    {
        std::thread thread1(foo);     // spawn new thread that calls foo()
        std::thread* thread2 = new std::thread(bar, 0);  // spawn new thread that calls bar(0)

        //thread2.swap(thread1);
        printf("main, foo and bar now execute concurrently...\n");
        // synchronize threads:
        //This blocks the execution of the thread that calls this function until the function called on construction returns (if it hasn't yet)
        //After a call to this function, the thread object becomes non-joinable and can be destroyed safely.

        if(thread1.joinable()) thread1.join();  // pauses until thread1 finishes
        printf("thread1 finished\n");
        if (thread2->joinable())  thread2->join(); // pauses until thread2 finishes
        printf("thread2 finished\n");

        //Detaches the thread represented by the object from the calling thread, allowing them to execute independently from each other
        //After a call to this function, the thread object becomes non-joinable and can be destroyed safely.
        //thread1.detach();
        //thread2->detach();

        printf("main thread finished\n");
        delete thread2;
    }
}

void test_thread()
{
   
    test_thread_::main();
}