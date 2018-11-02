﻿#include "test_random.h"
#include <iostream>
#include <random>
#include <string>
//This library allows to produce random numbers using combinations of generators and distributions:
    //Generators: Objects that generate uniformly distributed numbers.
    //Distributions : Objects that transform sequences of numbers generated by a generator into sequences of 
    //numbers that follow a specific random variable distribution, such as uniform, Normal or Binomial.
//Pseudo-random = giả ngẫu nhiên
void test_random()
{
    // uniform_int_distribution
    const int nrolls = 10000; // number of experiments
    const int nstars = 95;    // maximum number of stars to distribute

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 9);

    int p[10] = {};

    for (int i = 0; i<nrolls; ++i) {
        int number = distribution(generator);
        ++p[number];
    }

    std::cout << "uniform_int_distribution (0,9):" << std::endl;
    for (int i = 0; i<10; ++i)
        std::cout << i << ": " << std::string(p[i] * nstars / nrolls, '*') << std::endl;


    {
        const int nrolls = 10000;

        std::default_random_engine generator;
        std::bernoulli_distribution distribution(0.5);

        int count = 0;  // count number of trues

        for (int i = 0; i<nrolls; ++i) if (distribution(generator)) ++count;

        std::cout << "bernoulli_distribution (0.5) x 10000:" << std::endl;
        std::cout << "true:  " << count << std::endl;
        std::cout << "false: " << nrolls - count << std::endl;

    }
}