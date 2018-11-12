#include "test_decltype_auto.h"
#include <memory>
#include <assert.h>
#include <type_traits>
//The decltype(auto) type - specifier also deduces a type like auto does.However,
//it deduces return types while keeping their references and cv - qualifiers, while auto will not.

namespace test_decltype_auto_
{
    // Note: Especially useful for generic code!

    // Return type is `int`.
    auto f(const int& i) {
        return i;
    }

    // Return type is `const int&`.
    decltype(auto) g(const int& i) {
        return i;
    }


    void main()
    {
        const int x = 0;
        auto x1 = x; // int
        decltype(auto) x2 = x; // const int

        int y = 0;
        int& y1 = y;
        auto y2 = y1; // int
        decltype(auto) y3 = y1; // int&

        int&& z = 5;
        auto z1 = std::move(z); // int 
        decltype(auto) z2 = std::move(z); // int&& alias of z
        auto z3 = z; // int
        printf("z = 0x%x z1 = 0x%x z2 = 0x%x z3 = 0x%x\n", &z, &z1, &z2, &z3);

        {
            int x = 123;
            static_assert(std::is_same<const int&, decltype(f(x))>::value == 0,"fail 1");
            static_assert(std::is_same<int, decltype(f(x))>::value == 1, "fail 2");
            static_assert(std::is_same<const int&, decltype(g(x))>::value == 1, "fail 3");
        }
       
    }
}

void test_decltype_auto()
{
    test_decltype_auto_::main();

}