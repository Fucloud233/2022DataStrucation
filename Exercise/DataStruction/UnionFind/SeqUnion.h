#pragma once
#include "SeqUnion.h"
#include <iostream>
#include <map>
using namespace std;

template<class T>
class SeqUnion{
protected:
    map<T, T> data;
public:
    SeqUnion();
    SeqUnion(const int* arr, int lenght);
    
    void Union(T p, T q);
    bool connected(T p, T q) const;
    T find(T p) const;
    void insert(const T elem, const T leader);
    void insert(const T* arr, int lenght, const T leader);
    void erase(T elem);
    void print() const;
};

template<class T>
SeqUnion<T>::SeqUnion(){

}

template<class T>
SeqUnion<T>::SeqUnion(const int* arr, int length){
    for(int i=0;i<length;i++){
        data.insert(pair<int, int>(i, arr[i]));
    }
}

template<class T>
void SeqUnion<T>::Union(T p, T q){
    T a = find(p), b = find(q);
    for(auto it=data.begin();it!=data.end();it++){
        if(it->second==a){
            it->second = b;
        }
    }
}

template<class T>
bool SeqUnion<T>::connected(T p, T q) const{
    if(find(p)==find(q)){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
void SeqUnion<T>::print() const{
    for(auto it=data.begin();it!=data.end();it++){
        cout<<"["<<it->first<<"]: "<<it->second<<' ';
    }
    cout<<endl;
}

template<class T>
T SeqUnion<T>::find(T p) const{
    auto it = data.find(p);
    if(it==data.end()){
        return -1;
    }
    else{
        return it->second;
    }
}

template<class T>
void SeqUnion<T>::insert(const T elem, const T leader){
    bool flag = false;
    T group;
    
    // 对添加数组进行查找
    if(elem == leader){
        flag = true;
        group = leader;
    }   
    
    // 对原始数组进行查找
    if(!flag){
        auto it = data.find(leader);
        if(it==data.end()){
            cerr<<"[error] Don't have the leader!"<<endl;
            return;
        }

        group = it->second;
        while(group!=it->first){
            it = data.find(group);
            group = it->second;
        }
    }

    auto it = data.find(elem);

    if(it->second!=group){
        // 发生二义性 退出 并且删除原来数组
        if(it!=data.end()){
            cerr<<"[error] Element has ambiguity!"<<endl;
            return;
        }
        
        data.insert(pair<T, T>(elem, group));
    }
}

template<class T>
void SeqUnion<T>::insert(const T* arr, int length, const T leader){
    bool flag = false;
    T group;
    
    // 对添加数组进行查找
    for(int i=0;i<length;i++){
        if(arr[i]==leader){
            group = leader;
            flag = true;
            break;
        }
    }    
    
    // 对原始数组进行查找
    if(!flag){
        auto it = data.find(leader);
        if(it==data.end()){
            cerr<<"[error] Don't have the leader!"<<endl;
            return;
        }

        group = it->second;
        while(group!=it->first){
            it = data.find(group);
            group = it->second;
        }
    }

    for(int i=0;i<length;i++){
        auto it = data.find(arr[i]);

        if(it->second!=group){
            // 发生二义性 退出 并且删除原来数组
            if(it!=data.end()){
                cerr<<"[error] Element has ambiguity!"<<endl;
                for(int j=0;j<i;j++){
                    data.erase(arr[j]);
                }
                return;
            }
           
            data.insert(pair<T, T>(arr[i], group));
        }
    }
}

template<class T>
void SeqUnion<T>::erase(T elem){
    auto it = data.find(elem);
    if(it==data.end()){
        cerr<<"[error} Elem doesn't exist!"<<endl;
        return;
    }
    
    data.earse(elem);

    T leader = elem;
    if(it->first==it->second){
        // 首先找到替换leader
        for(it=data.begin();it!=data.end();it++){
            if(it->second==leader){
                it->second = it->first;
                leader = it->first;
                break;
            }
        }
        // 然后添加新的leader
        for(it++;it!=data.end();it++){
            if(it->second==leader){
                it->second = it->first;
            }
        }
    }

}

namespace seqUnion{
    void test(){
        int group[][3] = {{0, 5, 6}, {1, 2, 7}, {3, 4, 8}};
        int leader[] = {0, 1, 8};
        SeqUnion<int> s1;
        for(int i=0;i<3;i++){
            s1.insert(group[i], 3, leader[i]);
        }

        s1.print();

        int arr[] = {0, 1, 1, 8, 8, 0, 0, 1, 8};
        int len = 9;
        SeqUnion<int> s2(arr, len);
        s2.print();
        int a[] = {10, 11, 12, 13, 8};
        s2.insert(a, 5, 10);
        s2.print();
        s2.insert(19, 2);
        s2.print();
        cout<<s2.connected(2, 3)<<' '<<s2.connected(1, 2)<<endl;
        s2.Union(0, 1);
        s2.print();
    }
};
