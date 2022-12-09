#include "Stu.h"
#include <iostream>
using namespace std;

Student::Student()
    :Person(){
    this->NO = 0;
    this->score = 0;
}

Student::Student(string name, int NO, int score)
    :Person(name){
    this->NO = NO;
    this->score = score;
}

void Student::print(){
    
    cout<<NO<<' '<<score<<endl;
}

