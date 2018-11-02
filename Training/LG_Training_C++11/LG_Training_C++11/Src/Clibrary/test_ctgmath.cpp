#include "test_ctgmath.h"
#include <ctgmath> //(tgmath.h) C++11 //This header simply includes <cmath> and <ccomplex>
#include <iostream>
void test_ctgmath()
{
    int a = rint(3.4);//<cmath>

    //A complex number can be represented by the sum of a real number (x) and an imaginary part (y*i):
    //i2 = -1 
    std::complex<double> mycomplex(3.0, 4.0);

    std::cout << "The absolute value of " << mycomplex << " is " << std::abs(mycomplex) << '\n';

    std::complex<double> cos = std::cos(mycomplex);
    std::cout << "cosine of  =  " << mycomplex << " is "  << cos;
}