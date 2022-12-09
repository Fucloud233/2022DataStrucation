#pragma once

#include <iostream>
#include <vector>
using namespace std;

// 打印函数
template<class T>
void print(T* arr, int len){
    for(int i=0;i<len;i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}

template<class T>
void print(vector<T> arr){
    for(auto it=arr.begin();it!=arr.end();it++){
        cout<<*it<<' ';
    }
    cout<<endl;
}

