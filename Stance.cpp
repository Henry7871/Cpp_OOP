//
//  Stance.cpp
//  A2_OOP
//
//  Created by Henry_L on 24/5/20.
//  Copyright © 2020 Henry_L. All rights reserved.
//

#include <stdio.h>
#include<random>
#include<string>
#include<chrono>
#include<cmath>
#include "Header.h"
#include "randomNum.hpp"
using namespace std;
//static uniform_real_distribution<double> stanceUniform(-10, 10);

//extern unsigned seed;
//extern std::mt19937 mt_rand(seed);
Stance::Stance()
{
    significance = rDouble(-10, 10);
    approach     = rDouble(-10, 10);
//    range        = rDDouble(5);
}
Stance::Stance(double _range)
{
    significance = rDouble(-10, 10);
    approach     = rDouble(-10, 10);
    range        = rDDouble(0, _range);
}
double Stance::calculation(Stance* _stance)
{
    return sqrt(pow((approach-_stance->approach), 2)+pow((significance-_stance->significance), 2)) - range - _stance->range;
}
Stance::Stance(double _significance, double _approach, double _range)
{
    setSignificance(_significance);
    setApproach(_approach);
    setRange(_range);
}
Stance::Stance(double _significance, double _approach)
{
    setSignificance(_significance);
    setApproach(_approach);
}
double Stance::getSignificance(){
    return significance;
}
double Stance::getApproach(){
    return approach;
}
double Stance::getRange(){
    return range;
}
void   Stance::setSignificance(double _significance){
    significance = _significance;
}
void   Stance::setApproach(double _approach){
    approach = _approach;
}
void   Stance::setRange(double _range){
    range = _range;
}
void   Stance::display()
{
    cout << "Significance: " << significance << "\nApproach " << approach
            << "\nRange " << range <<'\n';
}
