//
//  Officials.cpp
//  A2_OOP
//
//  Created by Henry_L on 27/5/20.
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

Citizen::Citizen(){
    cid = rInteger(100, 999);
}
Citizen::Citizen(int _cid){
    cid = _cid;
}
Citizen::Citizen(int _cid, double _significance, double _approach, double _range){
    cid = _cid;
    setSignificance(_significance);
    setApproach(_approach);
    setRange(_range);
}
//void Citizen::setCitizen(int _cid, double _significance, double _approach, double _range){}
void Citizen::display()//virtual function
{
    cout << "Citizen No. " << cid << '\n';
    Stance::display();
}
int Citizen::getCID()
{
    return Citizen::cid;
}

Candidate::Candidate()
{
    double r = rDDouble(0, 2);
    setRange(r);
    popularity = 0;
    double c = rDDouble(0.9, 1.1);
    capability  = c;
    electorateNo = -1;
    int n = rInteger(-1, 2);
    partyType = PartyType(n);
}

Candidate::Candidate(Party* party, int idx)
{
    double r = rDDouble(0, 2);
    setRange(r);
    double p = rDDouble(-0.005, 0.005);
    popularity = p;
    double c = rDDouble(0.9, 1.1);
    capability  = c;
    electorateNo = idx;
    partyType = party -> getPartyType();

//    Party* pp = parties + (int)partyType;
    Party* pp = party;
    double dis = calculation(pp);//the distance between party stance and candidate stance
    double scope = pp -> getRange();
    
    if(dis > scope){
        double pApp = pp->getApproach();
        double pSig = pp->getSignificance();
        double A, S;
        if( (pApp-scope) >= -10 && (pApp+scope) <= 10){
            A = rDDouble(pApp-scope, pApp+scope);
        }
        else if((pApp-scope) < -10 && (pApp+scope) <= 10){
            A = rDDouble(10, pApp+scope);
        }
        else if((pApp+scope) > 10)
        {
            A = rDDouble(pApp-scope, 10);
        }
        else
        {
            A = rDDouble(-10, 10);
        }
        setApproach(A);
        double temp = sqrt(pow(scope, 2)-pow(pApp-A, 2));
        if( (pSig-temp) >= -10 && (pSig+temp) <= 10){
            S = rDDouble(pSig-temp, pSig+temp);
        }
        else if((pSig-temp) < -10 && (pSig+temp) <= 10){
            S = rDDouble(10, pSig+temp);
        }
        else if((pSig+temp) > 10)
        {
            S = rDDouble(pSig-temp, 10);
        }
        else
        {
            S = rDDouble(-10, 10);
        }
        setSignificance(S);
    }
}
double Candidate::calculation(Stance* _stance)//the distance between party stance and candidate stance
{
        double app = _stance->getApproach();
        double sig = _stance->getSignificance();
        return sqrt(pow((approach-app), 2)+pow((significance-sig), 2));
}
double Candidate::getPopularity(){
    return popularity;
}
void Candidate::calVote(Electorate arr[], Party parties[])
{
        arr[electorateNo].calvote(parties, electorateNo);
}
//void Candidate::addVote(double _candidateVote, double _totalVote, Electorate* p){}
void Candidate::display()//virtual function
{
    cout << "Candidate:" << '\n';
    Citizen::display();
    cout << "Popularity " << popularity << '\n'
        << "Capability " << capability << '\n'
        << "Electorate No. " << electorateNo + 1 << '\n'
        << "Party type " << partyType << '\n'
        <<"Current votes received " << vote << '\n';
}
long Candidate::getVote(){
    return vote;
}
void Candidate::setVote(long v){
    vote = v;
}
void Candidate::setpopularity(double t){
    popularity+=t;
}

ElectorateManager::ElectorateManager(){
    double r = rDDouble(0, 2);
    setRange(r);
    double c = rDDouble(0.9, 1.1);
    capability  = c;
    electorateNo = -1;
    int n = rInteger(-1, 2);
    partyType = PartyType(n);
}
ElectorateManager::ElectorateManager(Party* party, int idx){
    double r = rDDouble(0, 2);
    setRange(r);
    double c = rDDouble(0.9, 1.1);
    capability  = c;
    electorateNo = idx;
    partyType = party->getPartyType();

    //    Party* pp = parties + (int)partyType;
//    Party* pp = party;
    double dis = calculation(party);//the distance between party stance and candidate stance
    double scope = party -> getRange();
    double pApp = party->getApproach();
    double pSig = party->getSignificance();
    if(dis > scope){
            double A, S;
            if( (pApp-scope) >= -10 && (pApp+scope) <= 10){
                A = rDDouble(pApp-scope, pApp+scope);
            }
            else if((pApp-scope) < -10 && (pApp+scope) <= 10){
                A = rDDouble(10, pApp+scope);
            }
            else if((pApp+scope) > 10)
            {
                A = rDDouble(pApp-scope, 10);
            }
            else
            {
                A = rDDouble(-10, 10);
            }
            setApproach(A);
            double temp = sqrt(pow(scope, 2)-pow(pApp-A, 2));
            if( (pSig-temp) >= -10 && (pSig+temp) <= 10){
                S = rDDouble(pSig-temp, pSig+temp);
            }
            else if((pSig-temp) < -10 && (pSig+temp) <= 10){
                S = rDDouble(10, pSig+temp);
            }
            else if((pSig+temp) > 10)
            {
                S = rDDouble(pSig-temp, 10);
            }
            else
            {
                S = rDDouble(-10, 10);
            }
            setSignificance(S);
        }
}
double ElectorateManager::getCapability(){
    return capability;
}
long ElectorateManager::expense(Party* p,Electorate* e, long totalPopulation, int day){
    int n = this->electorateNo;
    long budget = 0.9*(p->getFund())*e[n].getPopulation()/(totalPopulation*day);
    return budget;
}
void ElectorateManager::changeFund(Party* p,long cost){
    double v = rDDouble(-0.003, 0.003);
    Candidate* cp = p->getCandidates();
    double old = cp[this->electorateNo].getPopularity();
    cp[this->electorateNo].setpopularity( old+v );
    cout << "The popularity of candidate from " << p->getPartyType() << " party has changed." << cp[this->electorateNo].getPopularity() << '\n' ;
//    cp[this->electorateNo].display();
    p->changeFund(cost);
}
void ElectorateManager::display()//virtual function
{
    cout << "Compaingn Manager:" << '\n';
    Citizen::display();
    cout << "Capability " << capability << '\n'
        << "Electorate No. " << electorateNo + 1 << '\n'
        << "Party type " << partyType << '\n';
}
    
Leader::Leader()
{
    double r = rDDouble(0, 2);
    setRange(r);
    popularity = 0;
    capability  = rDDouble(0.9, 1.1);
    int n = rInteger(-1, 2);
    partyType = PartyType(n);
}
Leader::Leader(Party* party)
{
    double r = rDDouble(0, 2);
    setRange(r);
    popularity = 0;
    partyType = party -> getPartyType();
    capability  = rDDouble(0.9, 1.1);
    double dis = calculation(party);//the distance between party stance and candidate stance
    double scope = party -> getRange();
    
    if(dis > scope){
        double pApp = party->getApproach();
        double pSig = party->getSignificance();
        double A, S;
        if( (pApp-scope) >= -10 && (pApp+scope) <= 10){
            A = rDDouble(pApp-scope, pApp+scope);
        }
        else if((pApp-scope) < -10 && (pApp+scope) <= 10){
            A = rDDouble(10, pApp+scope);
        }
        else if((pApp+scope) > 10)
        {
            A = rDDouble(pApp-scope, 10);
        }
        else
        {
            A = rDDouble(-10, 10);
        }
        setApproach(A);
        double temp = sqrt(pow(scope, 2)-pow(pApp-A, 2));
        if( (pSig-temp) >= -10 && (pSig+temp) <= 10){
            S = rDDouble(pSig-temp, pSig+temp);
        }
        else if((pSig-temp) < -10 && (pSig+temp) <= 10){
            S = rDDouble(10, pSig+temp);
        }
        else if((pSig+temp) > 10)
        {
            S = rDDouble(pSig-temp, 10);
        }
        else
        {
            S = rDDouble(-10, 10);
        }
        setSignificance(S);
    }
}
double Leader::calculation(Stance* _stance)//the distance between party stance and candidate stance
{
        double app = _stance->getApproach();
        double sig = _stance->getSignificance();
        return sqrt(pow((approach-app), 2)+pow((significance-sig), 2));
}
void Leader::setpopularity(double p){
    popularity += p;
}
double Leader::getPopularity(){
    return popularity;
}
void Leader::display()//virtual function
{
    cout << "Leader: " << '\n';
    Citizen::display();
    cout << "Popularity " << popularity << '\n'
        << "Capability " << capability << '\n'
    << "Party type " << partyType << '\n';
}

NationalManager::NationalManager(){
    double r = rDDouble(0, 2);
    setRange(r);
    double c = rDDouble(0.9, 1.1);
    capability  = c;
    int n = rInteger(-1, 2);
    partyType = PartyType(n);
}
NationalManager::NationalManager(Party* party){
    
    setRange(rDDouble(0, 2));
    capability  = rDDouble(0.9, 1.5);
    partyType = party -> getPartyType();
    double dis = calculation(party);//the distance between party stance and candidate stance
    double scope = party -> getRange();
    
    if(dis > scope){
        double pApp = party->getApproach();
        double pSig = party->getSignificance();
        double A, S;
        if( (pApp-scope) >= -10 && (pApp+scope) <= 10){
            A = rDDouble(pApp-scope, pApp+scope);
        }
        else if((pApp-scope) < -10 && (pApp+scope) <= 10){
            A = rDDouble(10, pApp+scope);
        }
        else if((pApp+scope) > 10)
        {
            A = rDDouble(pApp-scope, 10);
        }
        else
        {
            A = rDDouble(-10, 10);
        }
        setApproach(A);
        double temp = sqrt(pow(scope, 2)-pow(pApp-A, 2));
        if( (pSig-temp) >= -10 && (pSig+temp) <= 10){
            S = rDDouble(pSig-temp, pSig+temp);
        }
        else if((pSig-temp) < -10 && (pSig+temp) <= 10){
            S = rDDouble(10, pSig+temp);
        }
        else if((pSig+temp) > 10)
        {
            S = rDDouble(pSig-temp, 10);
        }
        else
        {
            S = rDDouble(-10, 10);
        }
        setSignificance(S);
    }
}
double NationalManager::getCapability(){
    return capability;
}
long NationalManager::expense(Party* p, int day){
    long budget = (p->getFund())/day;
    return budget;
}
void NationalManager::changeFund(Party* p,long cost){
    double v = rDDouble(-0.005, 0.005);
    Leader* leader = p->getLeader();
    leader->setpopularity(leader->getPopularity()+v);
    cout << "The popularity of leader has changed. " << leader->getPopularity() <<'\n';
//    leader->display();
    p->changeFund(cost);
}
void NationalManager::display()//virtual function
{
    cout << "National Manager:" << '\n';
    Citizen::display();
    cout << "Capability " << capability << '\n'
        << "Party type " << partyType << '\n';
}

FinancialManager::FinancialManager(){
    double r = rDDouble(0, 2);
    setRange(r);
    double c = rDDouble(0.9, 1.5);
    capability  = c;
    int n = rInteger(-1, 2);
    partyType = PartyType(n);
}
FinancialManager::FinancialManager(Party* party){
    
    setRange(rDDouble(0, 2));
    capability  = rDDouble(0.9, 1.5);
    partyType = party -> getPartyType();
    double dis = calculation(party);//the distance between party stance and candidate stance
    double scope = party -> getRange();
    
    if(dis > scope){
        double pApp = party->getApproach();
        double pSig = party->getSignificance();
        double A, S;
        if( (pApp-scope) >= -10 && (pApp+scope) <= 10){
            A = rDDouble(pApp-scope, pApp+scope);
        }
        else if((pApp-scope) < -10 && (pApp+scope) <= 10){
            A = rDDouble(10, pApp+scope);
        }
        else if((pApp+scope) > 10)
        {
            A = rDDouble(pApp-scope, 10);
        }
        else
        {
            A = rDDouble(-10, 10);
        }
        setApproach(A);
        double temp = sqrt(pow(scope, 2)-pow(pApp-A, 2));
        if( (pSig-temp) >= -10 && (pSig+temp) <= 10){
            S = rDDouble(pSig-temp, pSig+temp);
        }
        else if((pSig-temp) < -10 && (pSig+temp) <= 10){
            S = rDDouble(10, pSig+temp);
        }
        else if((pSig+temp) > 10)
        {
            S = rDDouble(pSig-temp, 10);
        }
        else
        {
            S = rDDouble(-10, 10);
        }
        setSignificance(S);
    }
}
long FinancialManager::raiseFund(Electorate* electorates, Party* party){
    int num = party->getNumEletorates();
    long totalFund = 0;
    for(int i = 0;i < num; i++){
        Candidate* cp = party->getCandidates();
        long a = cp[i].getVote();
        long b = electorates[i].getPopulation();
        double support = (double)a/b;
        totalFund += 0.05*electorates[i].getGDP() * (this->capability) * support;
    }
    return totalFund;
}
void FinancialManager::addFund(Party* party,long fund){
    party->addFund(fund);
    cout << "The new fund has been raised for " << (*party).getPartyType() << " party. " << fund << endl;
}
void FinancialManager::display()//virtual function
{
    cout << "Financial Manager:" << '\n';
    Citizen::display();
    cout << "Capability " << capability << '\n'
        << "Party type " << partyType << '\n';
}

