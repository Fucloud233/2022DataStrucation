#pragma once

#include <iostream>
#include <vector>
// 用来得到比较类型
#include <functional>
using namespace std;

template<class T, class CMP = greater<T>>
class BinaryHeap{
private:
    vector<T> data;
    CMP cmp;
    
    bool check(const T& elem);

    // 递归实现推化
    void heapifyRecursion(int index, int size);
    // 循环实现堆化
    void heapifyLoop(int currentIndex, int size);
    void heapify(int index, int size);

public:
    BinaryHeap();
    BinaryHeap(T* arr, int length);
    BinaryHeap(vector<T> arr);

    void sort();
    void push(const T& elem);
    void pop();
    int size();
    T top();
    T* getArr();
    void print(bool includeNewLine = false);
};

template<class T, class CMP>
BinaryHeap<T, CMP>::BinaryHeap(){
    this->data.push_back(T());
}

template<class T, class CMP>
BinaryHeap<T, CMP>::BinaryHeap(T *arr, int length){
    this->cmp = cmp;
    /* 建堆(heapify)和堆排序(heapSort)的区别
        1. 在堆的线性结构中 一个堆的起始值是从1开始的 
        而堆排序是对数组排序 (一般来说数组是从0开始的)
    */

    // 根据堆的插入方法 构建堆
    // data->push_back(T());
    // for(int i=0;i<length;i++){
    //     this->push(arr[i]);
    // }  
   
    // 根据堆化 构建堆
    data = vector<T>(arr, arr+length);
    data.insert(data.begin(), T());
    for(int i=length/2;i>=1;i--){
        this->heapify(i, data.size());
    }
}

template<class T, class CMP>
BinaryHeap<T, CMP>::BinaryHeap(vector<T> arr){
    this->cmp = cmp;
    // data.push_back(T());
    // for(auto it=arr.begin();it!=arr.end();it++){
    //     this->push(*it);
    // }

    // 根据堆化 构建堆
    data = arr;
    data.insert(data.begin(), T());
    for(int i=data.size()/2;i>=1;i--){
        this->heapify(i, data.size());
    }
}

template<class T, class CMP>
void BinaryHeap<T, CMP>::heapifyRecursion(int index, int size){
    int left = index*2, right = left + 1;
    int maxIndex = index;
    // 判断左节点
    if(left<size&&cmp(data[left], data[maxIndex])){
        maxIndex = left;
    }
    // 判断右节点
    if(right<size&&cmp(data[right], data[maxIndex])){
        maxIndex = right;
    }

    if(maxIndex!=index){
        swap(data[index], data[maxIndex]);
        heapifyRecursion(maxIndex, size);
    }
}

template<class T, class CMP>
void BinaryHeap<T, CMP>::heapifyLoop(int currentIndex, int size){
    int newIndex = currentIndex;

    while(true){
        int left = currentIndex*2, right = currentIndex*2+1;
        // 选取最大的子节点
        if(left<size&&cmp(data[left],data[newIndex])){
            newIndex = left;
        }
        if(right<size&&cmp(data[right],data[newIndex])){
            newIndex = right;
        }

        // 然后保持堆顺序
        if(newIndex!=currentIndex){
            swap(data[currentIndex], data[newIndex]);
            currentIndex = newIndex;
        }
        else
            break;
    }
}

template<class T, class CMP>
void BinaryHeap<T, CMP>::heapify(int index, int size){
    this->heapifyLoop(index, size);
    // this->heapifyRecursion(index, size);
}

template<class T, class CMP>
bool BinaryHeap<T, CMP>::check(const T& elem){
    auto it = find(data.begin(), data.end(), elem);
    if(it==data.end())
        return false;
    else
        return true;
}

template<class T, class CMP>
void BinaryHeap<T, CMP>::push(const T& elem){
    // 元素存在直接返回
    if(check(elem))
        return;

    // 插入元素
    data.push_back(elem);

    int currentIndex = data.size()-1;
    int preIndex = currentIndex/2;
    while(preIndex){
        if(cmp(data[currentIndex], data[preIndex])){
            swap(data[currentIndex], data[preIndex]);
            currentIndex = preIndex;
            preIndex /= 2;
        }
        else
            break;
    }
}
template<class T, class CMP>
int BinaryHeap<T, CMP>::size(){
    return this->data.size() - 1;
}

template<class T, class CMP>
T BinaryHeap<T, CMP>::top(){
    if(data.size()==1){
        cerr<<"[Error] Heap is empty!"<<endl;
        return T();
    }

    return data[1];
}

template<class T, class CMP>
void BinaryHeap<T, CMP>::pop(){
    if(data.size()==1){
        return;
    }

    // 1. 交换
    swap(data[1], data[data.size()-1]);
    // 2. 删除
    data.pop_back();
    // 3. 堆化
    this->heapify(1, data.size());

    // 进行heapify的过程(运用循环)
    // int currentIndex = 1, newIndex = currentIndex;
    // while(true){
    //     int left = currentIndex*2, right = currentIndex*2+1;
    //     // 选取最大的子节点
    //     if(left<data.size()&&cmp(data[left],data[newIndex])){
    //         newIndex = left;
    //     }
    //     if(right<data.size()&&cmp(data[right],data[newIndex])){
    //         newIndex = right;
    //     }

    //     // 然后保持堆顺序
    //     if(newIndex!=currentIndex){
    //         swap(data[currentIndex], data[newIndex]);
    //         currentIndex = newIndex;
    //     }
    //     else
    //         break;
    // }
}

template<class T, class CMP>
void BinaryHeap<T, CMP>::sort(){
    for(int i=data.size()-1;i>=1;i--){
        swap(data[1], data[i]);
        this->heapify(1, i);
    }
}

template<class T, class CMP>
void BinaryHeap<T, CMP>::print(bool includeNewLine){
    int index = 2;
    for(int i=1;i<data.size();i++){
        cout<<data[i]<<' ';

        if(i==index-1&&includeNewLine){
            index <<= 1;
            cout<<endl;
        }
    }
    cout<<endl;
}

template<class T, class CMP>
T* BinaryHeap<T, CMP>::getArr(){
    T* arr = new T[this->data.size()-1];
    for(int i=1;i<data.size();i++){
        arr[i] = data[i];
    }

    return arr;
}

