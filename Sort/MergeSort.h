#pragma once

#include<iostream>
#include"Assign.h"
using namespace std;

void merge_sort(int *arr, int left, int mid, int right){
    int len = right - left + 1;
    int* temp = new int[len];
    int i = left, j = mid+1, k = 0;

    while(i<=mid&&j<=right){
        if(arr[i]<=arr[j]){
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
        }
    }

    while(i<=mid){
        temp[k++] = arr[i++];
    }

    while(j<=right){
        temp[k++] = arr[j++];
    }

    for(k=0;k<len;k++){
        arr[left+k] = temp[k];
    }

    delete [] temp;
}


void mergeSort(int *arr, int left, int right){
    if(left<right){
        int mid = (left + right)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge_sort(arr, left, mid, right);
    }
}