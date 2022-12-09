#include "Person.h"
#include <iostream>
using namespace std;

Person::Person(string name){
    this->name = name;
}

void Person::print(){
    cout<<name<<endl;
}

