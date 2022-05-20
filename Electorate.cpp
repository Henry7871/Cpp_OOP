//
//  electorate.cpp
//  A2_OOP
//
//  Created by Henry_L on 26/5/20.
//  Copyright © 2020 Henry_L. All rights reserved.
//

#include <stdio.h>
#include<random>
#include<string>
#include<chrono>
#include<cmath>
#include "Header.h"
#include "Event.h"
#include "randomNum.hpp"
using namespace std;

Electorate::Electorate(){
    population   = rInteger(100000, 5000000);
    productivity = rDDouble(1.5, 5);
    GDP          = population * rDDouble(0.7, 1) * productivity;//productive population * productivity
    numGroups    = rInteger(3, 6);//num of groups is [5, 15]
    groups       = new Stance[numGroups];
    for(int i=0; i < numGroups; i++){

        groups[i] = Stance(5.0);
    }
    for(int i=0; i<4; i++){
        code += rInteger(65, 90);
    }
    _partyType = PartyType(-1);//The leading party in this electorate
}
Electorate::Electorate(const Electorate& e){
    code = e.code;
    population = e.population;
    productivity = e.productivity;
    GDP = e.GDP;
    numGroups = e.numGroups;
    _partyType = e._partyType;
    groups = new Stance[e.numGroups];
    for(int i = 0; i<numGroups; i++){
        groups[i] = e.groups[i];
    }
}
Electorate& Electorate::operator=(const Electorate& e){
    this->code = e.code;
    this->population = e.population;
    this->productivity = e.productivity;
    this->GDP = e.GDP;
    this->numGroups = e.numGroups;
    this->_partyType = e._partyType;
    this->groups = new Stance[e.numGroups];
    for(int i = 0; i<e.numGroups; i++){
        groups[i] = e.groups[i];
    }
    return *this;
}
Electorate::~Electorate(){
    delete [] groups;
}
Electorate::Electorate(string _code, long _population, long _GDP, int _n){
    code = _code;
    population = _population;
    GDP        = _GDP;
    numGroups  = _n;
    groups       = new Stance[numGroups];
    for(int i=0; i < numGroups; i++){
        groups[i] = Stance(5.0);
    }
}
long Electorate::getPopulation(){
    return population;
}
void Electorate::groupsVariation(double S, double A)//alternation of groups stance
{
    for(int i=0; i<numGroups; i++)
    {
        double s = groups[i].getSignificance();
        double a = groups[i].getApproach();
        if(S > s){
            groups[i].setSignificance(s+rDDouble(0, 0.05*(S-s)));
            if(A>a){groups[i].setApproach(a+rDDouble(0, 0.05*(A-a)));}
            else if(A<a){groups[i].setApproach(a-rDDouble(0, 0.05*(A-a)));}
            else{}
        }
        else if(S<s){
            groups[i].setSignificance(s-rDDouble(0, 0.05*(S-s)));
            if(A>a){groups[i].setApproach(a+rDDouble(0, 0.05*(A-a)));}
            else if(A<a){groups[i].setApproach(a-rDDouble(0, 0.05*(A-a)));}
            else{}
        }
    }
}
void Electorate::calvote(Party parties[], int j)//i refers to the subscript of candiates
{
    double totalvote = 0.0;
    double candidateVote[3]{0.0};
    for(int i = 0; i < numGroups; i++){
        int min_idx = -1;// recording the subscript of nearest candidate
        double temp = 15;//temp is max distance between two stances.
        double tmpVote = groups[i].getRange();
        double distance[3];
        for(int n = 0; n < 3; n++){
            Candidate* cp = parties[n].getCandidates() + j;//the j-th candidate
            distance[n] = groups[i].calculation(cp) - cp->getPopularity();
            if (distance[n] < temp){
                temp = distance[n];
                min_idx  = n;
            }
        }
        candidateVote[min_idx] += tmpVote;
        totalvote += tmpVote;
    }
    long max = 0;
    int idx_max = -1;
    for(int i = 0; i < 3; i++)
    {
        long vote = (candidateVote[i] / totalvote) * population;
        Candidate* candidates = parties[i].getCandidates();
        candidates[j].setVote(vote);
        if(vote > max){
            max = vote;
            idx_max = i;
        }
    }
    _partyType = parties[idx_max].getPartyType();
}
long Electorate::getGDP(){
    return GDP;
}
void Electorate::setPopulation(long p){
    population = p;
}
void Electorate::setGDP(long g){
    GDP = g;
}
PartyType Electorate::get_partyType(){
    return _partyType;
}
void Electorate::display()
{
    cout << "Electorate code: " << code << '\n'
            << "Population: " << population << '\n'
            << "Productivity " << productivity << '\n'
            << "GDP " << GDP << '\n'
            << "The most popular party: " << _partyType << '\n'
    << "The number of groups with various stances: " << numGroups << '\n';
    cout << "The details of groups in " << code << " electorate:";
    for(int id = 0;  id < numGroups;id++){
        cout << "\nGroup No. " << id+1 << '\n';
        groups[id].display();
    }
}


