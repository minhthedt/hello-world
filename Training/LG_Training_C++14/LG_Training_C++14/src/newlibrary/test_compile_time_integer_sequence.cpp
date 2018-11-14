#include "test_compile_time_integer_sequence.h"
#include <utility>
#include <array>
#include <tuple>
#include <iostream>
#include <string>
//https://blog.galowicz.de/2016/06/24/integer_sequences_at_compile_time/
namespace test_compile_time_integer_sequence_
{
    template<typename Array, std::size_t... I>
    decltype(auto) a2t_impl(const Array& a, std::integer_sequence<std::size_t, I...>) {
        return std::make_tuple(a[I]...);
    }

    template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
    decltype(auto) a2t(const std::array<T, N>& a) {
        return a2t_impl(a, Indices());
    }

    using std::tuple;

    static void func(double d, float f, int i)
    {
        std::cout << d << ", "
            << f << ", "
            << i << std::endl;
    }

    // The following code passes all parameters by 
    // value, for the sake of simplicity 

    template <typename F, typename TUP,int ... INDICES>
        static void tuple_call_(F f, TUP tup, std::integer_sequence<std::size_t, INDICES...>)
    {
        f(std::get<INDICES>(tup) ...);
    }

    template <typename F, typename ... Ts>
    static void tuple_call(F f, tuple<Ts...> tup)
    {
        tuple_call_(f, tup,
            std::make_index_sequence<sizeof...(Ts)>{});
    }

    void main()
    {
        
        std::array<int, 5> arr = { 1,2,3,4,5 };
        auto tup = a2t(arr);
        std::cout << std::tuple_size<decltype(tup)>::value << "\n";
        int p = std::get<0>(tup);


        func(1.1, 2.2, 3);

        tuple<double, float, int> tup1{ 1.1, 2.2, 3 };
        tuple_call(func, tup1); // same effect
    }
}

void test_compile_time_integer_sequence()
{
    using namespace  test_compile_time_integer_sequence_;
    main();
}

