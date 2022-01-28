//
// Created by 35196 on 20/01/2022.
//

#ifndef UNTITLED_LINE_H
#define UNTITLED_LINE_H

#include "string"
#include "vector"
#include "StopEdge.h"

using namespace std;

class Line {
private:
    string code;
    string name;
    vector<Stop> l0 = vector<Stop>();
    vector<Stop> l1= vector<Stop>();


public:
    Line();
    Line(const string &code, const string &name);
    ~Line();
    const string &getCode() const;
    const string &getName() const;
     vector<Stop> getL0();
     vector<Stop> getL1();
    void setL0(const vector<Stop> l0) ;
    void setL1(const vector<Stop> l1);
    void setCode(const string &code);
    void setName(const string &name);
    friend istream &operator>>(istream &is, Line &line);
};


#endif //UNTITLED_LINE_H
