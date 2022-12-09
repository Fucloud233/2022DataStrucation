#include <algorithm>
using namespace std;

// traverse from opposite endpoint
template<class T>
int partition1(T* arr, int begin, int end){
    // At fist, we record the middle number 
    int mid = arr[begin], l = begin, r = end;
    
    // And than, we exchange the number violating the order to mid
    // we maybe exchange arr[l] or arr[r]
    // but exactly, the number on the l/r is middle number
    while(l<r){
        while(l<r&&arr[r]>=mid){
            r--;
        }
        swap(arr[l], arr[r]);

        while(l<r&&arr[l]<=mid){
            l++;
        }
        swap(arr[l], arr[r]);
    }
    // using this method to partiation, 
    // we don't need move the mid to middle of arr

    // return the index of mid 
    return l;
}

// traverse from one endpoint
// it maybe more friendly for cpu visiting data
template<class T>
int partition2(T* arr, int begin, int end){
    int mid = arr[begin];
    int l = begin;
    // r pointer will move forward if the number is larger
    // and the next number of l pointer is larger too
    for(int r=begin+1;r<=end;r++){
        if(arr[r]<mid){
            swap(arr[++l], arr[r]);
        }
    }
    
    swap(arr[begin], arr[l]);
    return l;
}

template<class T>
void quickSort(T*arr, int begin, int end){
    // end the cursion
    if(begin>=end)
        return;
    
    int mid = partition2(arr, begin, end);
    quickSort(arr, begin, mid-1);
    quickSort(arr, mid+1, end);
}

#include <vector>
#include "Assign.h"

namespace testFun{
    void quickSortTest(){
        int len = 10;
        int* arr = getRandomArr(len);
        printArr(arr, len);
        quickSort(arr, 0, len-1);
        printArr(arr, len);
    } 
};

int main(){
    testFun::quickSortTest();
}