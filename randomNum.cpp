//
//  randomNum.cpp
//  A2_OOP
//
//  Created by Henry_L on 26/5/20.
//  Copyright © 2020 Henry_L. All rights reserved.
//

#include "randomNum.hpp"
#include<random>
//#include<string>
#include<chrono>
//#include<cmath>
using namespace std;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 mt_rand(seed);


double rDouble(double low, double high)
{
    static uniform_real_distribution<double> stanceUniform(low, high);
    return stanceUniform(mt_rand);
}
double rDDouble(double low, double high)
{
    uniform_real_distribution<double> stanceUniform(low, high);
    return stanceUniform(mt_rand);
}
int rInteger(int low, int high)
{
    uniform_int_distribution<unsigned> intUniform(low, high);
    return intUniform(mt_rand);
}
