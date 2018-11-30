#include "test_shared_ptr.h"
#include <string>
#include <memory>
#include <vector>
#include <iostream>

namespace test_shared_ptr_
{
    class Person
    {
    public:
        std::string name;
        std::shared_ptr<Person> mother;
        std::shared_ptr<Person> father;
        //std::vector<std::shared_ptr<Person>> kids;
        std::vector<std::weak_ptr<Person>> kids;

        Person(const std::string& n,
            std::shared_ptr<Person> m = nullptr,
            std::shared_ptr<Person> f = nullptr
        ) : name(n),mother(m), father(f)
        {};

        ~Person()
        {
            std::cout << "Delete..." << name.c_str() << std::endl;
        }
    };

    std::shared_ptr<Person> InitFamily(const std::string& name)
    {
        std::shared_ptr<Person> mon(new Person(name + "'s mom"));
        std::shared_ptr<Person> dad(new Person(name + "'s dad"));
        std::shared_ptr<Person> kid(new Person(name, mon,dad));
        mon->kids.push_back(kid);
        dad->kids.push_back(kid);
        return kid;
    };


    void main()
    {
        std::shared_ptr<Person> kid = nullptr;
        printf("kid_count = %d\n", kid.use_count());

        {
            kid = InitFamily("nico");
            printf("kid_count = %d mom_count = %d dad_count = %d \n", kid.use_count(), kid->mother.use_count(), kid->mother.use_count());
        }

        int kid_count = kid.use_count();
        int mom_count = kid->mother.use_count();
        int dad_count = kid->mother.use_count();
        printf("kid_count = %d mom_count = %d dad_count = %d \n", kid.use_count(), kid->mother.use_count(), kid->mother.use_count());


    }
}

void test_shared_ptr()
{
    test_shared_ptr_::main();
}