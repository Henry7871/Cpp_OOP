//
//  Issue.cpp
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

string getIssue(const IssueType& issueType)
{
    string s;
    switch ((int)issueType) {
        case 11:
            s = "Education";
            break;
        case 12:
            s = "Healthcare";
            break;
        case 13:
            s = "Taxation";
            break;
        case 14:
            s = "Employment";
            break;
        case 15:
            s = "Diplomacy";
            break;
        default:
            break;
    }
    return s;
}
Issue::Issue(){
    description  = "";
    double range = rDDouble(1,4);
    setRange(range);
//    significance = rDouble(-10, 10);
//    approach     = rDouble(-10, 10);
}
Issue::Issue(std::string _description):description(_description){
    double range = rDDouble(1, 4);
    setRange(range);
}
Issue::Issue(double _significance, double _approach, double _range, std::string _description): Stance(_significance, _approach, _range), description(_description){}
void Issue::display(){
    cout << "This issue is about " << description << endl;
    Stance::display();
}
void Issue::setDescription(std::string _string){
    description = _string;
}
string  Issue::getDescription(){
    return description;
}
