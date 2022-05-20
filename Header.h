//
//  Header.h
//  A2_OOP
//
//  Created by Henry_L on 24/5/20.
//  Copyright © 2020 Henry_L. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<ctime>
#include<chrono>


class Stance;
class Issue;
class Electorate;
class Party;
class Citizen;
class Leader;
class Candidate;
class FinancialManager;
class ElectorateManager;
class NationalManager;
class Event;
class Country;


enum class IssueType
{
    Education = 11,
    Healthcare,
    Taxation,
    Employment,
    Diplomacy
};
std::string getIssue(const IssueType& issueType);

enum class PartyType
{
    Left = 0,
    Neutral = 1,
    Right = 2,
    Independent = -1
    
};
std::ostream& operator<<(std::ostream& os, const PartyType& partyType);



class Stance
{
protected:
    double significance;//[-10, 10]
    double approach;//[-10, 10]
    double range = 0.0;//indicating the range of a specific stance point
public:
    Stance();
    Stance(double _range);
    Stance(double _significance, double _approach, double _range);
    Stance(double _significance, double _approach);
    double getSignificance();
    double getApproach();
    double getRange();
    void   setSignificance(double);
    void   setApproach(double);
    void   setRange(double);
    virtual double calculation(Stance* _stance);//dynamic_cast<Candidate>
    virtual void display();//=0
};

class Issue : public Stance
{
    std::string description;
public:
    Issue();
    Issue(std::string _description);
    Issue(double _significance, double _approach, double _range, std::string _description);
    virtual void   display();
    void    setDescription(std::string _string);
    std::string  getDescription();
};
class Citizen : public Stance
{
protected:
    int cid;
public:
    Citizen();
    Citizen(int);
    Citizen(int _cid, double _significance, double _approach, double _range);
//    void setCitizen(int _cid, double _significance, double _approach, double _range);
    virtual void display();
    int getCID();
};
class Candidate : public Citizen
{
    double      popularity;
    double      capability;
    PartyType   partyType;
    int         electorateNo;//electorate No.[0, 9]
    long        vote = 0;
public:
    Candidate();
    Candidate(Party* parties, int idx);
//    Candidate(PartyType _partyType, int idx);
//    Candidate(double _popularity, double _capability, PartyType _partyType, int n);
    virtual double calculation(Stance* _stance);
    double getPopularity();
    void setpopularity(double);
    void setVote(long);
    void    calVote(Electorate arr[], Party parties[]);
//    void    addVote(double _candidateVote, double _totalVote, Electorate* p);
    long    getVote();
    void    display();
};
class ElectorateManager : public Citizen
{
    double      capability;
    PartyType   partyType;
    int         electorateNo;//electorate No.[0, 9]
public:
    ElectorateManager();
    ElectorateManager(Party* party, int idx);
    double getCapability();
    long expense(Party*, Electorate*,long,int day);
    void changeFund(Party* p,long);
    void display();
    
};
class Leader : public Citizen
{
    double      popularity;
    double      capability;
    PartyType   partyType;
public:
    Leader();
    Leader(Party* party);
    virtual double calculation(Stance* _stance);
    double    getPopularity();
    void    setpopularity(double);
    void    display();
};
class NationalManager : public Citizen
{
    double      capability;
    PartyType   partyType;
public:
    NationalManager();
    NationalManager(Party* party);
    long expense(Party*, int day);
    double getCapability();
    void changeFund(Party* p,long);
    void display();
    
};
class FinancialManager : public Citizen
{
    double      capability;
    PartyType   partyType;
public:
    FinancialManager();
    FinancialManager(Party* party);
    long raiseFund(Electorate* e, Party* party);
    void addFund(Party* party, long fund);
    void display();
    
};
class Party : public Stance
{

    std::string         name;
    PartyType           partyType;
    Leader              leader;
    NationalManager     nationalManager;
    Candidate*          candidates;//arrary of candidates
    ElectorateManager*  electorateManagers;//array of ElectorateManagers
    FinancialManager    financialManager;
    long                fund;
    int                 numElectorates;
public:
    Party();
//    Party(std::string _name, PartyType _PartyType);
    Party(PartyType _PartyType, int n);// the number of electorates
    ~Party();
    Party(const Party&);
    Party& operator=(const Party&);
    long getFund() const;
    int getNumEletorates();
    PartyType getPartyType() const;
    Leader* const getLeader();
    NationalManager* const getNationalManager();
    FinancialManager* const getFinancialManager();
    Candidate* getCandidates() const;
    ElectorateManager* getElectorateManagers() const;
    void changeFund(long);
    void addFund(long);
    void display();
};
class Electorate
{

    std::string  code="";
//    int     num;
    double  productivity;
    long    population;
    long    GDP;
    Stance  *groups;//a dynamic array of stances (clusters)
    int     numGroups = 0;
    PartyType _partyType;
    
public:
    Electorate();
    ~Electorate();
    Electorate(const Electorate&);
    Electorate& operator=(const Electorate&);
    Electorate(std::string _code, long _population, long _GDP, int n);
    long getPopulation();
    void setPopulation(long);
    long getGDP();
    void setGDP(long);
    PartyType get_partyType();
    void setCode();
    void groupsVariation(double, double);//alternation of groups stance
    void calvote(Party parties[], int j);//i refers to the subscript of candiates
    void display();
};

class Country
{
    std::string  name;
    long    population;
    int     numElectorates = 0;
    Issue       issues[5];
    Party       parties[3];
    Electorate *electorates;
public:
//    std::string  name;
//    long    population;
//    int     numElectorates = 0;
    Country();
    Country(int);
    ~Country();
    Country(const Country&);
    Country& operator=(const Country&);
    Electorate* getElectorates();
    Party* getParties();
    Country(std::string _name, int num);//num refers to the number of electorate in a country
    long getPopulation();
    void setPopulation(long);
    int  getNumElectorates();
    void startCampaing(int day);
    void startElection();
    void display();
};

#endif /* Header_h */
