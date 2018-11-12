#include "test_lambda.h"
#include <iostream>
#include <string>
#include <functional>
namespace test_lambda_
{

	struct lambda1
	{
		template<typename A, typename B>
#if _MSC_VER > 1800 //c++14
		auto operator()(A a, B b) const // OK on VS 2017
#else
		auto operator()(A a, B b) const -> decltype(a * b)
#endif
		{
			return a * b;
		}
	};

	void main()
	{
		auto lambda = lambda1();
		auto foo4 = lambda(1, 2.5f);
		std::cout << foo4 << std::endl; //2.5f

		bool status = false;
		std::function<int(int, int)> sum = [&status](int a, int b) -> int
		{
			status = true;
			return a + b;
		};

		auto sum1 = sum(1, 2);
		printf("sum1 = %d status = %d\n",sum1,status);


		auto sum2 = [&status](int a, int b) ->  decltype(a + b)
		{
			status = true;
			return a + b;
		}(1,2);

		printf("sum2 = %d status = %d\n", sum2, status);

#if _MSC_VER > 1800
		//c++14
		auto nsum = [&status](auto a, auto b) -> decltype(a + b)
		{
			status = true;
			return a + b;
		};
#endif

	}
}

void test_lambda()
{
	test_lambda_::main();
}