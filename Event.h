//
//  Event.hpp
//  A2_OOP
//
//  Created by Henry_L on 31/5/20.
//  Copyright © 2020 Henry_L. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

#include<iostream>
#include<string>
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
class Country;
enum class IssueType;
enum class PartyType;
extern std::ostream& operator<<(std::ostream& os, const PartyType& partyType);
enum class EventType
{
    debate = 101,
    candidate = 102,
    leader = 104,
    issue = 103
};
std::ostream& operator<<(std::ostream& os, const EventType& eventType);


class Event
{
protected:
    int         day;
    Citizen*    c1;
    Citizen*    c2;
    Country*    country;
public:
    virtual ~Event(){};
    virtual void outcome() = 0;
    void setCitizens(Citizen*, Citizen*);
    void setNation(Country*);
    void setDay(int);
    virtual void display() = 0;
};
class LocalEvent: public Event
{
protected:
    int         numElectorate;
    EventType   eventType;
public:
    virtual ~LocalEvent(){};
    void setEventType(EventType _eventType);
    void setElectorate(int);
};
class LocalDebate:public LocalEvent//impact on stance distrubution on local electorate
{
protected:
    IssueType topic;
public:
    ~LocalDebate(){};
    LocalDebate(IssueType t, int day, Country* c, int numElectorate);
    void setTopic(IssueType);
    void outcome();
    void display();
};
class CandidateEvent:public LocalEvent
{
protected:
    std::string news;
public:
    virtual ~CandidateEvent(){};
    void setNews(std::string s);
};
class PositiveImpact:public CandidateEvent
{
public:
    ~PositiveImpact(){};
    PositiveImpact(std::string news, int day, Country* c, int numElectorate);
    void outcome();
    void display();
};
class NegativeImpact:public CandidateEvent
{
public:
    ~NegativeImpact(){};
    NegativeImpact(std::string news, int day, Country* c, int numElectorate);
    void outcome();
    void display();
};
class LocalIssue:public LocalEvent
{
protected:
    Issue* issue;
public:
    virtual ~LocalIssue(){};
    void setIssue(Issue*);
};
class LocalEconomy:public LocalIssue//impact on GDP of the electorate
{
public:
    ~LocalEconomy(){};
    LocalEconomy(Issue* i, int day, Country* c, int numElectorate);
    void outcome();
    void display();
    
};
class LocalSociety:public LocalIssue//impact on population of the electorate
{
public:
    ~LocalSociety(){};
    LocalSociety(Issue* i, int day, Country* c, int numElectorate);
    void outcome();
    void display();
    
};
class NationalEvent: public Event
{
protected:
    EventType   eventType;
public:
    virtual ~NationalEvent(){};
    void setEventType(EventType _eventType);
};
class NationalDebate:public NationalEvent
{
protected:
    IssueType topic;
public:
    ~NationalDebate(){};
    NationalDebate(IssueType _topic, int day, Country* c);
    void setTopic(IssueType);
    void outcome();
    void display();
};
class LeaderEvent:public NationalEvent
{
protected:
    std::string news;
public:
    virtual ~LeaderEvent(){};
    void setNews(std::string);
};
class PositiveLeaderEvent:public LeaderEvent
{
public:
    ~PositiveLeaderEvent(){};
    PositiveLeaderEvent(std::string news, int day, Country* c);
    void outcome();
    void display();
};
class NegativeLeaderEvent:public LeaderEvent
{
public:
    ~NegativeLeaderEvent(){};
    NegativeLeaderEvent(std::string news, int day, Country* c);
    void outcome();
    void display();
};
class NationalIssue:public LeaderEvent
{
protected:
    Issue* issue;
public:
    virtual ~NationalIssue(){};
    void setIssue(Issue*);
};
class NationalEconomy:public NationalIssue//impact on GDP of the electorate
{
public:
    ~NationalEconomy(){};
    NationalEconomy(Issue* i, int day, Country* c);
    void outcome();
    void display();
    
};
class NationalSociety:public NationalIssue//impact on population of the electorate
{
public:
    ~NationalSociety(){};
    NationalSociety(Issue* i, int day, Country* c);
    void outcome();
    void display();
    
};

#endif /* Event_hpp */
