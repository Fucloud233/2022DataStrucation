#pragma once

#include "Person.h"

class Student: public Person{
private:
    int NO, score;
public:
    Student();
    Student(string name, int NO, int score);
    void print();
};