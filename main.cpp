//
//  main.cpp
//  A2_OOP
//
//  Created by Henry_L on 24/5/20.
//  Copyright © 2020 Henry_L. All rights reserved.
//

#include <iostream>
#include"Header.h"
#include "Event.h"
#include"randomNum.hpp"
using namespace std;

class star{
    friend ostream& operator<<(ostream&, const star&);
private:
    int n;
public:
    star(int m){n = m;};
};
ostream& operator<<(ostream& os, const star& r){
    for(int i = 0;i<r.n;i++){
        os<<'*';}
    return os;
}
        
int main(int argc, const char * argv[]) {
    // insert code here...
//    Stance s1;
//    Stance s2;
//    Stance s3(4.34, 5.325);
//    s1.display();
//    cout << endl;
//    s2.display();
//    cout << endl;
//    s3.display();
//    cout << '\n' << s1.calculation(&s2);
//    cout << endl;
//    Issue I1;
//    Issue I2("Education");
//    Issue I3(2.344, 6.354, 3, "Healthcare");
//    I1.display();
//    I2.display();
//    I3.display();
//    cout << endl;
    
//    Electorate e1, e2;
//    e1.display();
//    e2.display();
//    Electorate* p = new Electorate[2];
//    p[0] = Electorate();
//    p[1] = Electorate();
//    p[1].display();
//    p[0].display();
//    cout << rInteger(5, 15) << endl;
//    cout << rInteger(100, 999) << endl;
//    Citizen c1;
//    c1.display();
//    Candidate C1;
//    C1.display();
//    Party p1;
//    p1.display();
    Country A(10);
//    A.display();
    cout << star(20) << endl;
    A.startCampaing(30);
    cout << star(20)<< endl;
    A.startElection();
    
//    A.display();
//    Electorate* ptr = A.getElectorates();
//    Party* pp = A.getParties();
//    ptr[0].display();
//    Candidate* cp = pp[0].getCandidates();
//    Candidate* cp1 = pp[1].getCandidates();
//    Candidate* cp2 = pp[2].getCandidates();
//    cp[0].display();
//    cp1[0].display();
//    cp2[0].display();
//    ptr[0].calvote(pp, 0);
//    cp[0].display();
//    cp1[0].display();
//    cp2[0].display();
//    A.display();
    return 0;
}
