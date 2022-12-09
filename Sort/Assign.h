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

template<class T>
int max(T* arr, int n){
    int maxIndex = 0;
    for(int i=1;i<n;i++){
        if(arr[i]>arr[maxIndex]){
            maxIndex = i;
        }
    }
    return maxIndex;
}

template<class T>
int min(T* arr, int n){
    int minIndex = 0;
    for(int i=1;i<n;i++){
        if(arr[i]<arr[minIndex]){
            minIndex = i;
        }
    }

    return minIndex;
}

void initialArr(int *arr, int n){
    for(int i=0;i<n;i++){
        arr[i] = 0;
    }
}