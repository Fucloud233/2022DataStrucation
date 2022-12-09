#pragma once

#include <iostream>
#include <functional>
#include "Assign.h"
using namespace std;

template<class T, class CMP>
void heapify(T* arr, int currentIndex, int size, CMP cmp){
    int newIndex = currentIndex;

    while(true){
        int left = currentIndex*2, right = currentIndex*2+1;
        // 选取最大的子节点
        if(left<size&&cmp(arr[left],arr[newIndex])){
            newIndex = left;
        }
        if(right<size&&cmp(arr[right],arr[newIndex])){
            newIndex = right;
        }

        // 然后保持堆顺序
        if(newIndex!=currentIndex){
            swap(arr[currentIndex], arr[newIndex]);
            currentIndex = newIndex;
        }
        else
            break;
    }
}

template<class T, class CMP = greater<T>>
void heapSort(T* arr, int length, CMP cmp = greater<T>()){
    //堆化
    for(int i=length/2-1;i>=0;i--){
        heapify(arr, i, length, cmp);
    }

    for(int i=length-1;i>0;i--){
        swap(arr[0], arr[i]);
        heapify(arr, 0, i, cmp);
    }
}

namespace heapTest{
    void sortTest(){
        char arr[] = "SORTEXAMPLE";
        int len = 11;
        heapSort(arr, len, less<char>());
        print(arr, len);
    }
}

// int main(){
//     heapTest::sortTest();
// }

