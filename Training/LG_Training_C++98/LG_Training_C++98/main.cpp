#include <stdio.h>
#include <string>


void main(int argn, char** argv)
{
	unsigned long long a = 12345612323432434ull;
	printf("a = %llu  \n",a);
	printf("_MSC_VER = %d\n", _MSC_VER);//_MSC_VER = 1600 (visual 2010)
	printf("hello world \n");
	getchar();
}