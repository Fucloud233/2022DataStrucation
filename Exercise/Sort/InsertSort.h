#pragma once

#include<iostream>
#include"assign.h"
using namespace std;

/* 插入排序算法1:
    从数组的前端开始遍历比较
*/
void insertSort1(int arr[], int n){
    int temp;
    for(int i=1;i<n;i++){
        // 从数组的前端开始比较
        for(int j=0;j<i;j++){
            //如果发生逆序则开始交换
            if(arr[j]>arr[i]){
                temp = arr[i];
                for(int k=i;k>j;k--){
                    arr[k] = arr[k-1];
                }
                arr[j] = temp;

                break;
            }
        }
    }
}

/* 插入排序算法2:
    从已排序好的后端往前查找
*/
void insertSort(int* arr, int n){
    for(int i=1;i<n;i++){
        int j = i - 1, temp = arr[i];
        while(j>=0&&arr[j]>temp){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

/* 插入排序算法3:
    在前面查找大于和小于与元素的时候 使用遍历查找
    如果使用二分查找将会更快
*/
// 二分查找 查找到较大的位置
template<class T>
int binarySearch(T *arr, T item, int low, int high){
    // 当范围缩小时 则返回较小的数
    if(high<=low){
        return (item>arr[low]) ? (low+1) : low;
    }

    // 找到中位数
    int mid = (low + high)/2;
    if(item>arr[mid]){
        return binarySearch(arr, item, mid + 1, high);
    }
    return binarySearch(arr, item, low, mid-1);
}

template<class T>
void binaryInsertSort(T *arr, int n){
    for(int i=1;i<n;i++){
        int index = binarySearch(arr, arr[i], 0, i-1), j = i-1;
        
        T temp = arr[i];
        while(j>=index){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

/* 插入排序算法4:
    希尔排序
*/
void shellSort(int* arr, int n){
    // 用于控制间隙的大小
    for(int gap=n/2;gap>0;gap/=2){
        // 如果当gap=1时 实质上与插入排序相同
        /* 分组排序
            从理论上讲 应该先排序玩一个的所有元素 再去排序下一个组
            但如果采用何种方法排序 每次跳跃后需要折返回来 会比较麻烦
            对于插入排序而言 只要将每个元素进行插入即可
            所以无所谓插入的先后
        */
        for(int i=gap;i<n;i++){
            int j = i - gap, temp = arr[i];
            while(j>=0&&arr[j]>temp){
                arr[j+gap] = arr[j];
                j-=gap;
            }
            arr[j+gap] = temp;
        }
    }
}