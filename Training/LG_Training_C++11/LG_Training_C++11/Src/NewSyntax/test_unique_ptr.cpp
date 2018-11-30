#include <string>
#include <memory>
#include <vector>
#include <iostream>


namespace test_unique_ptr_
{
    class A
    {
    public:
        int a;
        A() :a(0) {};
        A(int in) : a(in) { a = in; };
        void print() { printf("A::printf a = %d\n", a); }
    };

    std::unique_ptr<A> pass_through(std::unique_ptr<A> p)
    {
        p->a = 6;
        return p;
    }

    void main()
    {
        //std::unique_ptr<A> up = std::make_unique<A>();
        std::unique_ptr<A> up(new A(12));
        up->print();
        //std::unique_ptr<A> b = up;//ERROR
        std::unique_ptr<A> b = std::move(up);//OK up == nullptr
        std::unique_ptr<A> c = pass_through(std::move(b));//b == nullptr
        std::shared_ptr<A> sp(c.release());
        sp->print();
        if (!b) printf("b == nullptr\n");
        if (!c) printf("c == nullptr\n");

    }
}

void test_unique_ptr()
{
    test_unique_ptr_::main();
}