#include "test_condition_variable.h"
#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>


namespace test_condition_variable_
{

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    void print_id(int id) {
        std::unique_lock<std::mutex> lck(mtx);
        while (!ready) cv.wait(lck);
        // ...
        std::cout << "thread " << id << '\n';
    }

    void go() {
        std::unique_lock<std::mutex> lck(mtx);
        ready = true;
        cv.notify_all();
        //for (int i = 0; i < 10; i++)
        //{
        //    cv.notify_one();
        //}
    }

    void main()
    {
        std::thread threads[10];
        // spawn 10 threads:
        for (int i = 0; i<10; ++i)
            threads[i] = std::thread(print_id, i);

        std::cout << "10 threads ready to race...\n";
        printf("press any key to notify_all threads ");
        getchar();

        go();                       // go!

        for (auto& th : threads) th.join();
    }

    //std::mutex mutex_;
    //std::condition_variable condVar;

    //bool dataReady{ false };

    //void waitingForWork() {
    //    printf("Waiting \n");
    //    std::unique_lock<std::mutex> lck(mutex_);//mutex_.lock();
    //    condVar.wait(lck, [] { return dataReady; });   // (4)
    //    printf("Running \n");
    //}

    //void setDataReady() 
    //{
    //    {
    //        std::lock_guard<std::mutex> lck(mutex_);
    //        dataReady = true;
    //    }
    //    printf("Data prepared \n");
    //    condVar.notify_one();                        // (3)
    //}


    //void main()
    //{
    //    std::cout << std::endl;

    //    std::thread t1(waitingForWork);               // (1)
    //    std::thread t2(setDataReady);                 // (2)

    //    t1.join();
    //    t2.join();

    //    std::cout << std::endl;
    //}

}
//A condition variable is an object able to block the calling thread until notified to resume.
void test_condition_variable()
{
    test_condition_variable_::main();
}