#pragma once

#include<iostream>
using namespace std;

template<class T>
void printArr(T *arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i] <<' ';
    }
    cout<<endl;
}

// print a vector array
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

// generate a random array
int* getRandomArr(int len=10){
    int* arr = new int[len];
    
    // get a basic random array
    for(int i=0;i<len;i++){
        arr[i] = rand()%50;
    }
    // shuffle the array again
    for(int i=0;i<len;i++){
        int index = rand()%(len-i) + i;
        swap(arr[i], arr[index]);
    }

    return arr;
}