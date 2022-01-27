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
    vector<int> l0 = vector<int>();
    vector<int> l1= vector<int>();


public:
    Line();
    Line(const string &code, const string &name);
    ~Line();
    const string &getCode() const;
    const string &getName() const;
     vector<int>& getL0();
     vector<int>& getL1();
    void setL0(const vector<int> l0) ;
    void setL1(const vector<int> l1);
    void setCode(const string &code);
    void setName(const string &name);
    friend istream &operator>>(istream &is, Line &line);
};


#endif //UNTITLED_LINE_H
