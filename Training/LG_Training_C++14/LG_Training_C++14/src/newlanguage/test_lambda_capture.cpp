#include "test_lambda_capture.h"
#include <memory>
//This allows creating lambda captures initialized with arbitrary expressions.The name given to the captured value does not need to be related to any variables 
//in the enclosing scopes and introduces a new name inside the lambda body.The initializing expression is evaluated when the lambda is created(not when it is invoked).


namespace test_lambda_capture_
{
    
    // possible to move (or forward) values into a lambda
    void test1()
    {
        std::unique_ptr<int> p = std::make_unique<int>(1);

        //auto task1 = [=] { *p = 5; }; // ERROR: std::unique_ptr cannot be copied
                                      // vs.
        auto task2 = [pp = std::move(p)]{ *pp = 5; }; // OK: pp is move-constructed into the closure object
                                                    // the original p is empty after task2 is created

        if (p == nullptr) printf("p == nullptr\n");
    }

    //Using this reference-captures can have different names than the referenced variable.
    void test2()
    {
        auto x = 1;
        auto f = [&r = x, x = x * 10](){
            ++r;
        return r + x;
        };
        f(); // sets x to 2 and returns 12
    }


    int factory(int i) { return i * 10; }
    void main()
    {
        auto f = [x = factory(2)](void) { return x; }; // returns 20

        auto lambda = [x = f()](){ return x; };

        auto generator = [x = 0]() mutable {
            // this would not compile without 'mutable' as we are modifying x on each call
            return x++;
        };

        auto a = generator(); // == 0
        auto b = generator(); // == 1
        auto c = generator(); // == 2
    }

}

void test_lambda_capture()
{
    test_lambda_capture_::main();
}
