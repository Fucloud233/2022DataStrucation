#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "stdlib.h"
using namespace std;

// 打印函数
template<class T>
void printArr(T* arr, int len){
    for(int i=0;i<len;i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}

template<class T>
void printArr(vector<T> arr){
    if(!arr.size()){
        cout<<"[Error] Arr is empty!"<<endl;
        return;
    }

    for(auto it=arr.begin();it!=arr.end();it++){
        cout<<*it<<' ';
    }
    cout<<endl;
}

template<class T>
void print(T& data){
    cout<<data<<endl;
}

template<class T>
void print(string title, T data){
    cout<<title<<": "<<data<<endl;
}

// 返回一个随机序列
vector<int> getRandomArr(int length=10, int size=50, int seed=0){
    srand(seed);
    vector<int> arr;
    for(int i=0;i<length;i++){
        arr.push_back(rand()%size);
    }

    return arr;
}

int getRandomNum(int size=50, int seed=1){
    srand(seed);
    return rand()%size;
}