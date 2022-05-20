//
//  Country.cpp
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
#include "Event.h"
#include "randomNum.hpp"
using namespace std;

Country::Country()
{
    int n = rInteger(1, 10);
    numElectorates = n;
    for(int i=0; i<2; i++){
        name += rInteger(65, 90);
    }
    for(int i = 0; i<5; i++){
        string topic = getIssue(IssueType(11+i));
        issues[i] = Issue(topic);
        if(i < 3){
            parties[i] = Party(PartyType(i), numElectorates);
        }
    }
    
    electorates = new Electorate[n];
    for (int j=0; j<n; j++){
        electorates[j] = Electorate();
        population += electorates[j].getPopulation();
    }
    
}
Country::Country(int n)
{
    numElectorates = n;
    for(int i=0; i<2; i++){
        name += rInteger(65, 90);
    }
    for(int i = 0; i<5; i++){
        string topic = getIssue(IssueType(11+i));
        issues[i] = Issue(topic);
        if(i < 3){
            parties[i] = Party(PartyType(i), numElectorates);
        }
    }
    
    electorates = new Electorate[n];
    for (int j=0; j<n; j++){
        electorates[j] = Electorate();
        population += electorates[j].getPopulation();
    }
    
}
Country::~Country(){
//    for(int i = 0; i<numElectorates; i++){
//        electorates[i].~Electorate();
//    }
    delete [] electorates;
    
}
Country::Country(const Country& c){
    name = c.name;
    numElectorates = c.numElectorates;
    population = c.population;
    electorates = new Electorate[c.numElectorates];
    for(int i = 0; i < 5; i++){
        issues[i] = c.issues[i];
        if(i<3){
            parties[i] = c.parties[i];
        }
    }
    for(int i = 0; i<c.numElectorates; i++){
        electorates[i] = c.electorates[i];
    }
}
Country& Country::operator=(const Country& c){
    this->name = c.name;
    this->numElectorates = c.numElectorates;
    this->population = c.population;
    this->electorates = new Electorate[c.numElectorates];
    for(int i = 0; i < 5; i++){
        this->issues[i] = c.issues[i];
        if(i<3){
            this->parties[i] = c.parties[i];
        }
    }
    for(int i = 0; i<c.numElectorates; i++){
        this->electorates[i] = c.electorates[i];
    }
    return *this;
}
Country::Country(std::string _name, int num)//num refers to the number of electorate in a country
{
    
}
Electorate* Country::getElectorates(){
    return electorates;
}
long Country::getPopulation(){
    return population;
}
void Country::setPopulation(long p){
    population = p;
}
Party* Country::getParties(){
    return parties;
}
int Country::getNumElectorates()
{
    return numElectorates;
}
void Country::display(){
    cout << "Country name: " << name << '\n'
        << "Population: " << population << '\n'
    << "The number of electorates: " << numElectorates <<'\n'
    << "The details on each electorate " << '\n';
    for(int i = 0; i < numElectorates; i++){
        electorates[i].display();
        cout << endl;
    }
    cout << "The details on each of three parties " << '\n';
    for(int i = 0; i<3; i++){
        parties[i].display();
        cout << endl;
    }
    cout << "The details on each of five issues in this election" <<'\n';
    for(int i = 0; i < 5; i++){
        issues[i].display();
        cout << endl;
    }
}
void Country::startCampaing(int day){
    cout << "Start campaign......\n";
    ElectorateManager* eManagers0 = parties[0].getElectorateManagers();
    ElectorateManager* eManagers1 = parties[1].getElectorateManagers();
    ElectorateManager* eManagers2 = parties[2].getElectorateManagers();
    
    NationalManager* nManager0 = parties[0].getNationalManager();
    NationalManager* nManager1 = parties[1].getNationalManager();
    NationalManager* nManager2 = parties[2].getNationalManager();
    
    FinancialManager* fManager0 = parties[0].getFinancialManager();
    FinancialManager* fManager1 = parties[1].getFinancialManager();
    FinancialManager* fManager2 = parties[2].getFinancialManager();
    
    for(int n = day; n>0; n--){
        if(n>1){
            cout << '\n' << n << " days away from Election\n" << endl;
        }
        else{cout << '\n' << n << " day away from Election\n" << endl;}
        
        //national event
        int national_occurence = rInteger(1, 100);
        if(national_occurence <=30){
            Event* NE = NULL;
            switch(national_occurence%5){
                case 0:{
                     NE = new NationalDebate(IssueType(rInteger(11, 15)),n, this);
                    break;
                }
                case 1:{
                    string news = getIssue(IssueType(rInteger(11, 15)));
                    NE = new PositiveLeaderEvent(news,n, this);
                    break;
                }
                case 2:{
                    string news = getIssue(IssueType(rInteger(11, 15)));
                     NE = new NegativeLeaderEvent(news,n, this);
                    break;
                }
                case 3:{
                    NE = new NationalEconomy(issues+rInteger(0, 4),n, this);
                    break;
                }
                case 4:{
                    NE = new NationalSociety(issues+rInteger(0, 4),n, this);
                    break;
                }
                default:
                    NE = NULL;
                    break;
            }
            if(NE!=NULL){
                NE->outcome();
                NE->display();
            }
            delete NE;
        }
        for(int i=0; i<numElectorates; i++){
            
            cout << "\nIn Electorate No." << i+1 << "\n";
            //local event for each electorate
            int occurrence = rInteger(1, 100);
            if(occurrence <= 20){
                Event* E=NULL;
                switch(occurrence%5){
                    case 0:{
                         E = new LocalDebate(IssueType(rInteger(11, 15)),n, this, i);
                        break;
                    }
                    case 1:{
                        string news = getIssue(IssueType(rInteger(11, 15)));
                         E = new PositiveImpact(news,n, this, i);
                        break;
                    }
                    case 2:{
                        string news = getIssue(IssueType(rInteger(11, 15)));
                         E = new NegativeImpact(news,n, this, i);
                        break;
                    }
                    case 3:{
                        E = new LocalEconomy(issues+rInteger(0, 4),n, this, i);
                        break;
                    }
                    case 4:{
                        E = new LocalSociety(issues+rInteger(0, 4),n, this, i);
                        break;
                    }
                    default:
                        E = NULL;
                        break;
                }
                if(E!=NULL){
                    E->outcome();
                    E->display();
                }
                delete E;
            }
            
            
            long cost0 = eManagers0[i].expense(parties+0, electorates, population, n);
            eManagers0[i].changeFund(parties+0, cost0);
            long cost1 = eManagers1[i].expense(parties+1, electorates, population, n);
            eManagers1[i].changeFund(parties+1, cost1);
            long cost2 = eManagers2[i].expense(parties+2, electorates, population, n);
            eManagers2[i].changeFund(parties+2, cost2);
            
            electorates[i].calvote(parties, i);
            
        }
        
        long nCost0 = nManager0->expense(parties+0, n);
        nManager0->changeFund(parties+0, nCost0);
        long nCost1 = nManager1->expense(parties+1, n);
        nManager1->changeFund(parties+1, nCost1);
        long nCost2 = nManager2->expense(parties+2, n);
        nManager2->changeFund(parties+2, nCost2);
        if(n!=1){
            long fund0 = fManager0->raiseFund(electorates, parties+0);
            fManager0->addFund(parties+0, fund0);
            long fund1 = fManager1->raiseFund(electorates, parties+1);
            fManager1->addFund(parties+1, fund1);
            long fund2 = fManager2->raiseFund(electorates, parties+2);
            fManager2->addFund(parties+2, fund2);
        }
        
    }
    
}
void Country::startElection(){
    int ElectionResults[3]{0};
    for(int i = 0; i<numElectorates; i++){
        
        switch(electorates[i].get_partyType()){
            case PartyType(0):{++ElectionResults[0];break;}
            case PartyType(1):{++ElectionResults[1];break;}
            case PartyType(2):{++ElectionResults[2];break;}
            default: cout << electorates[i].get_partyType();break;
        }
    }
    int max = 0, idx = -1;
    cout << "Election results:\n";
    for(int i = 0; i<3; i++){
        cout << PartyType(i) << " party has won " << ElectionResults[i] << " electorate(s).\n";
        if(ElectionResults[i]>max){
            max = ElectionResults[i];
            idx = i;
        }
    }
    cout << "Country Status:\n";
    if(numElectorates%2 == 0){
        if(max >= numElectorates/2){
            cout << "The new government has been formed by " << PartyType(idx) << " party.\n"
            << "The new national leader is present on details as below\n";
            parties[idx].getLeader()->display();
        }
        else{
            cout << "Hung Parliament." << endl;
        }
    }
    else{
        if(max > numElectorates/2){
            cout << "The new government has been formed by " << PartyType(idx) << " party.\n"
            << "The new national leader is present on details as below\n";
            parties[idx].getLeader()->display();
        }
        else{
            cout << "Hung Parliament." << endl;
        }
    }
}
