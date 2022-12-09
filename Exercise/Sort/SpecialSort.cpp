#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
#include "Assign.h"
#include "ExchangeSort.h"
using namespace std;
                                     
int* getOrder(int *arr, int n, int minNum){
    // 通过minNum 来限定整个数组的范围
    int len = arr[max(arr, n)] + 1 - minNum;
    int *countingArr = new int[len];
    initialArr(countingArr, len);
    // 首先对数字进行计数
    for(int i=0;i<n;i++){
        countingArr[arr[i]-minNum]++;
    }

    // 然后产生序列
    for(int i=1;i<len;i++){
        countingArr[i] += countingArr[i-1];
    }

    return countingArr;
}

void countingSort(int *arr, int n){
    int minNum = arr[min(arr, n)];
    int* order = getOrder(arr, n, minNum);
    int* result = new int[n];

    // 根据排列顺序 放入到结果数组中
    for(int i=0;i<n;i++){
        result[--order[arr[i]-minNum]] = arr[i];
    }

    // 将排序结果 放回原数组
    for(int i=0;i<n;i++){
        arr[i] = result[i];
    }
    delete[] result, order;
}

// 生成一个规格化数组
float* normalize(float *arr, int n)
{
    int maxNum = max(arr, n), minNum = min(arr, n);
    float *res = new float[n];
    for(int i=0;i<n;i++){
        res[i] = (arr[i]-minNum)/(maxNum - minNum);
    }
    return res;
}

// 桶排序
void bucketSort(float *arr, int n){
    int num = 5;    // 桶的大小
    vector<vector<float>> bucket(num);
    float* res = new float[n];
    
    // 所有数据转换为桶的序号 然后存放在数据中
    for(int i=0;i<n;i++){
        bucket[(int)res[i]*num].push_back(arr[i]);
    }

    for(int i=0;i<num;i++){
        sort(bucket[i].begin(), bucket[i].end());
    }

    // 再将所有的数据进行合并
    int index = 0;
    for(int i=0;i<num;i++){
        for(int j=0;j<bucket[i].size();j++){
            arr[index++] = bucket[i][j];
        }
    }
}

// 基数排序
void base_sort(char **arr, int n, vector<pair<int, int>>& pos){
    // 终止递归的条件: 当划分数组为0时
    if(pos.size()<1){
        return;
    }
    
    // 根据划分数组排序
    for(int k=0;k<pos.size();k++){
        int begin = pos[k].first, end = pos[k].second;

        // 首先排序划分数组
        for(int i=begin+1;i<=end;i++){
            int j = i - 1;
            char *temp = arr[i];
            while(j>=0&&arr[j][n]>arr[i][n]){
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = temp;
        }

        // 然后在对该数组进行划分
        vector<pair<int, int>> nextPos;
        int i = begin;
        while(i<=end){
            // 当为'\0'时 不需要载入
            if(!arr[i][n]){
                i++;
                continue;
            }

            // 记录划分序列
            int first = i;
            while(i+1<=end&&arr[i][n]==arr[i+1][n]){
                i++;
            }
            int last = i++;

            // 当划分序列中只有一个 则不需要载入
            if(last-first)
                nextPos.push_back(pair<int, int>(first, last));
        }

        // 进行下一层级划分
        base_sort(arr, n+1, nextPos);
    }
}

void baseSort(char **arr, int n){
    vector<pair<int, int>> s;
    s.push_back(pair<int, int>(0, n-1));
    base_sort(arr, 0, s);
}

// 进行划分
int partition(int *arr, int left, int right){
    int l = left, r = left+1;
    int center = arr[left]; 
    while(r<=right){
        if(arr[r]<center){
            swap(arr[r], arr[++l]);
        }
        r++;
    }

    swap(arr[l], arr[left]);
    return l;
}

int binaryFind(int *arr, int begin, int end, int k){
    int center = partition(arr, begin, end);
    int temp = center - begin + 1;
    if(k==temp){
        return arr[center];
    }
    else if(k<temp){
        return binaryFind(arr, begin, center-1, k);
    }
    else{
        return binaryFind(arr, center+1, end, k-temp);
    }
}

int main(){
    int len = 7;
    int arr[] = {2, 9, 7, 5, 1, 8, 4};
    // char *arr[] = {"sea", "she", "seashell", "shells", "shore", "she", "shells"};
    // char *arr[] = {"hello", "my", "friend"};
    // char *arr[] = {"bac", "abc", "bab"};
    print(arr, len);
    // baseSort(arr, len);
    cout<<binaryFind(arr, 0, len-1, 4);
}