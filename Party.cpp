//
//  Party.cpp
//  A2_OOP
//
//  Created by Henry_L on 28/5/20.
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

std::ostream& operator<<(std::ostream& os, const PartyType& partyType){
    switch ((int)partyType) {
        case -1:{
            os << "Independent";
            break;
        }
        case 0:{
            os << "Left";
            break;
        }
        case 1:{
            os << "Neutral";
            break;
        }
        case 2:{
            os << "Right";
            break;
        }
        default:
            break;
    }
    return os;
}

Party::Party(){
    for(int i=0; i<3; i++){
        name += rInteger(65, 90);
    }
    int n = rInteger(0, 2);
    partyType = PartyType(n);
    double approach;
    double significance;
    double range;
    if (n == 0){
        approach = rDDouble(-10, 0);
        if(approach < -5){significance = rDDouble(-10, 10);}
        else {
            double t = rDDouble(-10, 10);
            double d = pow(5, 2)-pow(0-approach, 2);
            while(pow(t,2) <= d){
             t=rDDouble(-10, 10);
            }
            significance = t;
        }
        range = rDDouble(3, 6);
        setApproach(approach);
        setSignificance(significance);
        setRange(range);
    }
    else if(n==2){
        approach = rDDouble(0, 10);
        if(approach > 5){significance = rDDouble(-10, 10);}
        else {
            double t = rDDouble(-10, 10);
            double d = pow(5, 2)-pow(0-approach, 2);
            while(pow(t,2) <= d){
             t=rDDouble(-10, 10);
            }
            significance = t;
        }
        range = rDDouble(3, 6);
        setApproach(approach);
        setSignificance(significance);
        setRange(range);
    }
    else{
        double approach = rDDouble(-5, 5);
        double temp = sqrt(pow(5, 2)-pow(0-approach, 2));
        double significance = rDDouble(0-temp, 0+temp);
        double range = rDDouble(3, 6);
        setApproach(approach);
        setSignificance(significance);
        setRange(range);
    }
    leader = Leader(this);
    nationalManager = NationalManager(this);
    financialManager = FinancialManager(this);
            numElectorates = 0;
    
}
Party::Party(PartyType _PartyType, int n)
{
    for(int i=0; i<3; i++){
        name += rInteger(65, 90);
    }
    partyType = _PartyType;
    numElectorates = n;
    double approach;
    double significance;
    double range;
    if ((int)partyType == 0){
        approach = rDDouble(-10, 0);
        if(approach < -5){significance = rDDouble(-10, 10);}
        else {
            double t = rDDouble(-10, 10);
            double d = pow(5, 2)-pow(0-approach, 2);
            while(pow(t,2) <= d){
             t=rDDouble(-10, 10);
            }
            significance = t;
        }
        range = rDDouble(3, 6);
        setApproach(approach);
        setSignificance(significance);
        setRange(range);
    }
    else if((int)partyType==2){
        approach = rDDouble(0, 10);
        if(approach > 5){significance = rDDouble(-10, 10);}
        else {
            double t = rDDouble(-10, 10);
            double d = pow(5, 2)-pow(0-approach, 2);
            while(pow(t,2) <= d){
             t=rDDouble(-10, 10);
            }
            significance = t;
        }
        range = rDDouble(3, 6);
        setApproach(approach);
        setSignificance(significance);
        setRange(range);
    }
    else{
        double approach = rDDouble(-5, 5);
        double temp = sqrt(pow(5, 2)-pow(0-approach, 2));
        double significance = rDDouble(0-temp, 0+temp);
        double range = rDDouble(3, 6);
        setApproach(approach);
        setSignificance(significance);
        setRange(range);
    }
    leader = Leader(this);
    nationalManager = NationalManager(this);
    financialManager = FinancialManager(this);
    candidates = new Candidate[numElectorates];
    electorateManagers =  new ElectorateManager[numElectorates];
    for(int i = 0; i < numElectorates; i++){
        candidates[i] = Candidate(this, i);
        electorateManagers[i] = ElectorateManager(this, i);
    }
    fund = rInteger(10000000, 100000000);//millions to tens of millions
}
Party::~Party(){
    delete [] candidates;
    delete [] electorateManagers;
}
Party::Party(const Party& p){
    partyType = p.partyType;
    numElectorates = p.numElectorates;
    name = p.name;
    fund = p.fund;
    leader = p.leader;
    nationalManager = p.nationalManager;
    financialManager = p.financialManager;
    candidates = new Candidate[p.numElectorates];
    electorateManagers = new ElectorateManager[p.numElectorates];
    for(int i = 0; i<p.numElectorates; i++){
    candidates[i] = p.candidates[i];
    electorateManagers[i] = p.electorateManagers[i];
    }
}
Party& Party::operator=(const Party& p){
            this->partyType = p.partyType;
            this->numElectorates = p.numElectorates;
            this->name = p.name;
            this->fund = p.fund;
            this->leader = p.leader;
            this->nationalManager = p.nationalManager;
            this->financialManager = p.financialManager;
            this->candidates = new Candidate[p.numElectorates];
            this->electorateManagers = new ElectorateManager[p.numElectorates];
            for(int i = 0; i<p.numElectorates; i++){
                candidates[i] = p.candidates[i];
                electorateManagers[i] = p.electorateManagers[i];
            }
            return *this;
            }

PartyType Party::getPartyType() const{
            return partyType;
}
Leader* const Party::getLeader(){
    return &(this->leader);
}
NationalManager* const Party::getNationalManager(){
    return &(this->nationalManager);
}
FinancialManager* const Party::getFinancialManager(){
    return &(this->financialManager);
}
Candidate* Party::getCandidates() const{
    return candidates;
}
ElectorateManager* Party::getElectorateManagers() const{
    return electorateManagers;
}
long Party::getFund() const{
    return fund;
}
int Party::getNumEletorates()
{
    return numElectorates;
}
void Party::changeFund(long f){
    fund -= f;
}
void Party::addFund(long f){
    fund += f;
}
void Party::display(){
//    double r = rDDouble(0, 5);
//    setRange(r);
    cout << "Party name: " << name << '\n'
    << "Party type " << partyType << '\n'
    << "The fund for election: " << getFund() << '\n';
    Stance::display();
    leader.display();
    nationalManager.display();
    financialManager.display();
    for(int i = 0; i < numElectorates; i++){
        cout << "In No. " << i+1 << " electorate" <<'\n';
        candidates[i].display();
        electorateManagers[i].display();
    }
            
}
