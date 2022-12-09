#pragma once

#include<iostream>
#include"assign.h"
#include"InsertSort.h"
using namespace std;

// 冒泡排序
void BubbleSort(int* arr, int n){
    for(int i=0;i<n-1;i++){
        for(int j=1;j<n-i;j++){
            if(arr[j-1]>arr[j]){
                swap(arr[j-1], arr[j]);
            }
        }
    }
}

int partition1(int *arr, int low, int high){
    int l = low, r = high, p =arr[low];
    while(l<r){
        // 将右边小的数往左边移动
        while(l<r&&arr[r]>=p){
            r--;
        }
        swap(arr[l], arr[r]);
        
        // 将左边小的数往右边移动
        while(l<r&&arr[l]<=p){
            l++;
        }
        swap(arr[r], arr[l]);
    }
    return l;
}

int partition2(int* arr, int low, int high){
    int pivot = arr[low];
    int i = low;

    for(int j=low+1;j<=high;j++){
        if(arr[j]<pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // 将开头的指针 移动中间来
    swap(arr[low], arr[i]);
    return i;
}

const int SHORTEST = 2;

// 快速排序
void quickSort(int* arr, int low, int high){
    if(low<high){
        // 当数组序列比较小的时候 利用插入排序会更快
        if(high-low+1<=SHORTEST){
            insertSort(arr+low, high-low);
        }

        // 获得基准位置 分别对两边排序 然后对左右两边的函数进行排序
        int pivot = partition1(arr, low, high);
        quickSort(arr, low, pivot-1);
        quickSort(arr, pivot+1, high);
    }
}