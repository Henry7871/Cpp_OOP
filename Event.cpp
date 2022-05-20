//
//  Event.cpp
//  A2_OOP
//
//  Created by Henry_L on 31/5/20.
//  Copyright © 2020 Henry_L. All rights reserved.
//

#include "Event.h"
#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<ctime>
#include<chrono>
#include "Header.h"
#include "randomNum.hpp"
using namespace std;

std::ostream& operator<<(std::ostream& os, const EventType& eventType){
    switch ((int)eventType) {
        case 101:{
            os << "debate";
            break;
        }
        case 102:{
            os << "candidate";
            break;
        }
        case 103:{
            os << "issue";
            break;
        }
        case 104:{
            os << "leader";
            break;
        }
        default:
            break;
    }
    return os;
}

void Event::setCitizens(Citizen* x1, Citizen* x2)
{
    c1 = x1;
    c2 = x2;
}
void Event::setNation(Country* _country)
{
    country = _country;
}
void Event::setDay(int _day)
{
    day = _day;
}
void LocalEvent::setEventType(EventType _eventType)
{
    eventType = _eventType;
}
void LocalEvent::setElectorate(int n)
{
    numElectorate = n;
}
LocalDebate::LocalDebate(IssueType t, int day, Country* c, int numElectorate)
{
    setEventType(EventType(101));
    setTopic(t);
    setDay(day);
    setNation(c);
    setElectorate(numElectorate);
}
void LocalDebate::setTopic(IssueType t)
{
    topic = t;
}
void LocalDebate::outcome()
{
//    Candidate* candidates = dynamic_cast<Candidate*>(c1);
//    ElectorateManager* eManagers = dynamic_cast<ElectorateManager*>(c2);
    Party* parties = country->getParties();
    int winner = rInteger(0, 2);
    Candidate* candidates = parties[winner].getCandidates();
    double S = candidates[numElectorate].getSignificance();
    double A = candidates[numElectorate].getApproach();
    
    c1 = &(candidates[numElectorate]);
            
    Electorate* electorates = country->getElectorates();
    electorates[numElectorate].groupsVariation(S,A);
    electorates[numElectorate].calvote(parties, numElectorate);
}
void LocalDebate::display()
{
    cout << "Local Event type: " << eventType << '\n'
            << " in day " << day << '\n'
            << "Debate Topic: " << getIssue(topic) << '\n'
            << "The details of winner in this local debate:" <<'\n';
            c1->display();
    cout << "The groups of stances in Electorate No." << numElectorate+1
            <<" have been changed as below " << '\n';
    Electorate* electorates = country->getElectorates();
    electorates[numElectorate].display();
}

void CandidateEvent::setNews(string s){
    news = s;
}
PositiveImpact::PositiveImpact(string news, int day, Country* c, int numElectorate)
{
            setEventType(EventType(102));
            setNews(news);
            setDay(day);
            setNation(c);
            setElectorate(numElectorate);
}
void PositiveImpact:: outcome()
{
            int partyType = rInteger(0, 2);
            Party* parties = country->getParties();
            Candidate* candidates = parties[partyType].getCandidates();
            ElectorateManager* eManagers = parties[partyType].getElectorateManagers();
            c1 = &(candidates[numElectorate]);
            c2 = &(eManagers[numElectorate]);
            double effect = rDDouble(0.1, 0.3);
            double capability = eManagers[numElectorate].getCapability();
            double old_popularity = candidates[numElectorate].getPopularity();
            candidates[numElectorate].setpopularity(old_popularity+effect*capability);
            
            Electorate* electorates = country->getElectorates();
            electorates[numElectorate].calvote(parties, numElectorate);
}
void PositiveImpact::display()
{
            cout << "Local Event type: " << eventType << '\n'
                    << " in day " << day << '\n'
                    << "Candidate News: " << news << '\n'
                    << "The support of candidate has increased in this local event:" <<'\n';
                    c1->display();
}
NegativeImpact::NegativeImpact(std::string news, int day, Country* c, int numElectorate)
{
            setEventType(EventType(102));
            setNews(news);
            setDay(day);
            setNation(c);
            setElectorate(numElectorate);
}
void NegativeImpact::outcome()
{
           int partyType = rInteger(0, 2);
           Party* parties = country->getParties();
           Candidate* candidates = parties[partyType].getCandidates();
           ElectorateManager* eManagers = parties[partyType].getElectorateManagers();
           c1 = &(candidates[numElectorate]);
           c2 = &(eManagers[numElectorate]);
           double effect = rDDouble(-0.3, -0.1);
           double capability = eManagers[numElectorate].getCapability();
           double old_popularity = candidates[numElectorate].getPopularity();
           candidates[numElectorate].setpopularity(old_popularity+effect*capability);
           
           Electorate* electorates = country->getElectorates();
           electorates[numElectorate].calvote(parties, numElectorate);
}
void NegativeImpact::display()
{
            cout << "Local Event type: " << eventType << '\n'
            << " in day " << day << '\n'
            << "Candidate News: " << news << '\n'
            << "The support of candidate has decreased in this local event:" <<'\n';
            c1->display();
}
void LocalIssue::setIssue(Issue* p)
{
            issue = p;
}
LocalEconomy::LocalEconomy(Issue* i, int day, Country* c, int numElectorate)
{
            setEventType(EventType(103));
            setIssue(i);
            setDay(day);
            setNation(c);
            setElectorate(numElectorate);
}
void LocalEconomy::outcome()
{
            double effect = rDDouble(0.8, 1.2);
            Electorate* electorates = country->getElectorates();
            long new_GDP = electorates[numElectorate].getGDP()*effect;
            electorates[numElectorate].setGDP(new_GDP);
            cout << "Local envent happens...\n";
            if(effect < 1){
            cout<< "The GDP of No." << numElectorate << " electorate has declined to " << new_GDP << ".\n";
            }
            else if(effect > 1){
            cout<< "The GDP of No." << numElectorate << " electorate has increased to " << new_GDP << ".\n";
            }
            else{
            cout<< "The GDP of No." << numElectorate << " electorate has not influenced.\n";
            }
}
            
void LocalEconomy::display()
{
            cout << issue->getDescription() << '\n';
            cout << "Local Event type: " << eventType << '\n'
                               << " in day " << day << '\n'
            << "Issue details: " << '\n';
            issue->display();
            
}
LocalSociety::LocalSociety(Issue* i, int day, Country* c, int numElectorate)
{
            setEventType(EventType(103));
            setIssue(i);
            setDay(day);
            setNation(c);
            setElectorate(numElectorate);
}
void LocalSociety::outcome()
{
            cout << "Local event happens...\n";
            double effect = rDDouble(0.9, 1.1);
            Electorate* electorates = country->getElectorates();
            long old_population = electorates[numElectorate].getPopulation();
            long new_population = old_population*effect;
            electorates[numElectorate].setPopulation(new_population);
            if(effect < 1){
            cout<< "The population of No." << numElectorate << " electorate has declined to " << new_population << ".\n";
            }
            else if(effect > 1){
            cout<< "The population of No." << numElectorate << " electorate has increased to " << new_population << ".\n";
            }
            else{
            cout<< "The population of No." << numElectorate << " electorate has not influenced.\n";
            }
            //update population
            country->setPopulation(country->getPopulation()-old_population+new_population);
            Party* parties = country->getParties();
            electorates[numElectorate].calvote(parties, numElectorate);
            
}
void LocalSociety::display()
{
            cout << issue->getDescription() << '\n';
            cout << "Local Event type: " << eventType << '\n'
                               << " in day " << day << '\n'
            << "Issue details: " << '\n';
            issue->display();
}

void NationalEvent::setEventType(EventType _eventType){
    eventType = _eventType;
}


NationalDebate::NationalDebate(IssueType _topic, int day, Country* c){
    setEventType(EventType(101));
    setTopic(_topic);
    setDay(day);
    setNation(c);
}
void NationalDebate::setTopic(IssueType i){
    topic = i;
}
void NationalDebate::outcome(){
            Party* parties = country->getParties();
                int winner = rInteger(0, 2);
                Leader* leaders = parties[winner].getLeader();
                double S = leaders->getSignificance();
                double A = leaders->getApproach();
                
                c1 = leaders;
                        
                Electorate* electorates = country->getElectorates();
            int n = country->getNumElectorates();
            for(int i = 0; i<n; i++){
                electorates[i].groupsVariation(S,A);
                electorates[i].calvote(parties, i);
                cout << "The groups of stances in Electorate No. " << i+1
                    <<" have been changed." << '\n';
//                electorates[i].display();
            }
}
void NationalDebate::display(){
            cout << "National Event type: " << eventType << '\n'
                    << " in day " << day << '\n'
                    << "Debate Topic: " << getIssue(topic) << '\n'
                    << "The details of winner in this national debate:" <<'\n';
                    c1->display();
}

void LeaderEvent::setNews(string s){
    news = s;
}

PositiveLeaderEvent::PositiveLeaderEvent(string news, int day, Country* c){
    setEventType(EventType(104));
    setNews(news);
    setDay(day);
    setNation(c);
}
void PositiveLeaderEvent::outcome(){
    int partyType = rInteger(0, 2);
    Party* parties = country->getParties();
    Leader* leader = parties[partyType].getLeader();
    NationalManager* nManager = parties[partyType].getNationalManager();
    
    Candidate* candidates = parties[partyType].getCandidates();
    
    c1 = leader;
    c2 = nManager;
    double effect = rDDouble(0.15, 0.3);
    double capability = nManager->getCapability();
    cout << "National Event happens...\n";
    for(int i = 0; i<country->getNumElectorates(); i++){
        double old_popularity = candidates[i].getPopularity();
        candidates[i].setpopularity(old_popularity+effect*capability);
    
        Electorate* electorates = country->getElectorates();
        electorates[i].calvote(parties, i);
        cout << "The popularity of candidate in Electorate No. " << i+1
            <<" have been changed." << '\n';
//        candidates[i].display();
        }
}
            
void PositiveLeaderEvent::display(){
            cout << "National Event type: " << eventType << '\n'
            << " in day " << day << '\n'
            << "Leader News: " << news << '\n'
            << "The support of candidates has increased in this national event due to the positive impacts from" <<'\n';
            c1->display();
}

NegativeLeaderEvent::NegativeLeaderEvent(string news, int day, Country* c){
    setEventType(EventType(104));
    setNews(news);
    setDay(day);
    setNation(c);
}
void NegativeLeaderEvent::outcome(){
            int partyType = rInteger(0, 2);
            Party* parties = country->getParties();
            Leader* leader = parties[partyType].getLeader();
            NationalManager* nManager = parties[partyType].getNationalManager();
            
            Candidate* candidates = parties[partyType].getCandidates();
            
            c1 = leader;
            c2 = nManager;
            double effect = rDDouble(-0.3, -0.15);
            double capability = nManager->getCapability();
            cout << "National Event happens...\n";
            for(int i = 0; i<country->getNumElectorates(); i++){
                double old_popularity = candidates[i].getPopularity();
                candidates[i].setpopularity(old_popularity+effect*capability);
            
                Electorate* electorates = country->getElectorates();
                electorates[i].calvote(parties, i);
                cout << "The popularity of candidate in Electorate No. " << i+1
                    <<" have been changed." << '\n';
//                candidates[i].display();
            }
}
void NegativeLeaderEvent::display(){
            cout << "National Event type: " << eventType << '\n'
                << " in day " << day << '\n'
                << "Leader News: " << news << '\n'
                << "The support of candidates has decreased in this national event due to the negative impacts from" <<'\n';
            c1->display();
}

void NationalIssue::setIssue(Issue* i){
    issue = i;
}

NationalEconomy::NationalEconomy(Issue* i, int day, Country* c){
    setEventType(EventType(103));
    setIssue(i);
    setDay(day);
    setNation(c);
}
void NationalEconomy::outcome(){
            
            Electorate* electorates = country->getElectorates();
            cout << "National event happens...\n";
            for(int i = 0; i<country->getNumElectorates(); i++){
                double effect = rDDouble(0.8, 1.2);
                long new_GDP = electorates[i].getGDP()*effect;
                electorates[i].setGDP(new_GDP);
                if(effect < 1){
                cout<< "The GDP of No." << i+1 << " electorate has declined to " << new_GDP << ".\n";
                }
                else if(effect > 1){
                cout<< "The GDP of No." << i+1 << " electorate has increased to " << new_GDP << ".\n";
                }
                else{
                cout<< "The GDP of No." << i+1 << " electorate has not influenced.\n";
                }
            }
}
void NationalEconomy::display(){
            cout << issue->getDescription() << '\n';
            cout << "Nationl Event type: " << eventType << '\n'
                               << " in day " << day << '\n'
            << "Issue details: " << '\n';
            issue->display();
            }

NationalSociety::NationalSociety(Issue* i, int day, Country* c){
    setEventType(EventType(103));
    setIssue(i);
    setDay(day);
    setNation(c);
}
void NationalSociety::outcome(){
            double effect = rDDouble(0.9, 1.1);
            Electorate* electorates = country->getElectorates();
            long totalPopulation = 0;
            cout << "National event happens...\n";
            for(int i = 0; i<country->getNumElectorates(); i++){
                long old_population = electorates[i].getPopulation();
                long new_population = old_population * effect;
                electorates[i].setPopulation(new_population);
                totalPopulation += new_population;
                if(effect < 1){
                cout<< "The population of No." << i+1 << " electorate has declined to " << new_population << ".\n";
                }
                else if(effect > 1){
                cout<< "The population of No." << i+1 << " electorate has increased to " << new_population << ".\n";
                }
                else{
                cout<< "The population of No." << i+1 << " electorate has not influenced.\n";
                }
            }
            
            
            //update population and support
            country->setPopulation(totalPopulation);
            Party* parties = country->getParties();
            for(int i = 0; i<country->getNumElectorates(); i++){
                electorates[i].calvote(parties, i);
            }
}
void NationalSociety::display(){
            cout << issue->getDescription() <<'\n';
            cout << "National event type: " << eventType << '\n'
                               << " in day " << day << '\n'
            << "Issue details: " << '\n';
            issue->display();
}
