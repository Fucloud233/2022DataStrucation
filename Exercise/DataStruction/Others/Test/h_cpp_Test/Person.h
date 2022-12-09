#pragma once

#include<string>
using namespace std;

class Person{
protected:
    string name;
public:
    Person(string n="None");
    void print();
};