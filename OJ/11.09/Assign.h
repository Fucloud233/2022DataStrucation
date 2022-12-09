#pragma once

#include<iostream>
using namespace std;

template<class T>
void print(T *arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i] <<' ';
    }
    cout<<endl;
}
