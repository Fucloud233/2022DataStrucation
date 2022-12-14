#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
class UnionNode{
public:
    T leader;
    int size;
    vector<T> child;
    UnionNode(){
        this->leader = T(NULL);
        this->size = 0;
    }

    UnionNode(T leader, int size=0){
        this->leader = leader;
        this->size = size;
    }
};

template<class T>
class QuickUnion{
private:
    map<T, UnionNode<T>> data;
public:
    QuickUnion();
    QuickUnion(const int* arr, int length);

    void Union(T p, T q);
    bool connected(T p, T q) const;
    T find(T p);
    bool insert(const T elem, const T leader);
    bool insert(const T* arr, int lenght, const T leader);
    bool erase(T elem);
    void print(bool includeNewLine=false, bool includeChild=false, bool includeSize=false) const;

};

template<class T>
QuickUnion<T>::QuickUnion(){ }

// 直接使用基类的构造函数
template<class T>
QuickUnion<T>::QuickUnion(const int* arr, int length){
    for(int i=0;i<length;i++){
        this->insert(i, arr[i]);
    }
}

template<class T>
void QuickUnion<T>::Union(T p, T q){
    // 查找到父类元素
    p = this->find(p); q = this->find(q);   
    if(p==q){
        return;
    }

    if(data[p].size>data[q].size)
        swap(p, q);
    
    data[p].leader = q; 
    data[q].child.push_back(p);
    data[q].size += data[p].size;
}

template<class T>
bool QuickUnion<T>::connected(T p, T q) const{
    if(find(p)==find(q)){
        return true;
    }
    else{
        return false;
    }
}

// 插入单个元素
template<class T>
bool QuickUnion<T>::insert(T elem, T leader){
    bool newLeader = false;

    // 1. 判断leadere的情况
    if(data.find(leader)==data.end()){
        // 如果只是单独节点 那么直接添加
        this->data.insert(pair<T, UnionNode<T>>(leader, UnionNode<T>(leader, 1)));
        if(elem==leader){
            return true;
        }
        newLeader = true;
    }
    
    // 2. 元素插入
    // 元素不存在->直接插入
    if(this->data.find(elem)==data.end()){
        data.insert(pair<T, UnionNode<T>>(elem, UnionNode<T>(leader, 1)));
        data[leader].child.push_back(elem);
    }
    // 元素存在->是相同节点->则不需要重复插入
    else if(this->data[elem].leader==leader){
        return true;
    }
    // 元素存在->是根节点->则改变他的头节点
    else if(this->data[elem].leader==elem){
        // 判断元素和节点是否交叉引用
        if(data[leader].leader==elem){
            cerr<<"[Error] "<<elem<<' '<<leader<<" has cross-reference!"<<endl;
            return false;
        }
        data[elem].leader = leader;
        data[leader].child.push_back(elem);
    }
    // 元素存在->不是根节点->leader不同->发生二义性
    else if(this->data[elem].leader!=leader){
        cerr<<"[Error] "<<elem<<" has ambiguity!"<<endl;
        // 插入失败->创建了根节点->删除根节点
        if(newLeader){
            data.erase(leader);
        }
        return false;
    }

    // size传递
    while(this->data[elem].leader!=elem){
        this->data[data[elem].leader].size += data[elem].size;
        elem = this->data[elem].leader;
    }

    return true;
}

template<class T>
bool QuickUnion<T>::insert(const T* arr, int length, const T leader){
    for(int i=0;i<length;i++){
        if(!insert(arr[i], leader)){
            return false;
        }
    }

    return true;
}

// 返回一个元素的根节点
template<class T>
T QuickUnion<T>::find(T p){
    auto it = this->data.find(p);
    if(it==this->data.end()){
        cerr<<"[Error] Don't have this elem!"<<endl;
        return T(NULL);
    }

    while(p!=this->data[p].leader){
        p = this->data[p].leader;
    }

    return p;
}

template<class T>
bool QuickUnion<T>::erase(T elem){
    if(data.find(elem)==data.end()){
        cerr<<"[Error] "<<elem<<" does not exist!"<<endl;
        return false;
    }

    T leader = data[elem].leader;   //记录leader
    // 删除元素不是根节点->需要重新选定节点
    if(data[elem].size!=1){
        // 找size最小的子树 用于替换
        vector<T>& elemchild = data[elem].child;
        auto minIt = elemchild.begin(); // 利用迭代器来记录最小子树
        for(auto it=elemchild.begin()+1;it!=elemchild.end();it++){
            if(data[*it].size<data[*minIt].size){
                minIt = it;
            }
        }
        data[leader].child.push_back(*minIt);
        
        // 对这个子树进行处理
        for(int i=0;i<elemchild.size();i++){
            if(elemchild[i]!=*minIt)
                data[*minIt].child.push_back(elemchild[i]);
        }
        data[*minIt].leader = leader;
        data[*minIt].size += data[elem].size - 2;
    }

    // 1. 减少顶部的size
    T temp = elem;
    while(this->data[temp].leader!=temp){
        this->data[data[temp].leader].size--;
        temp = this->data[temp].leader;
    }

    // 2. 删除顶部的 子节点
    vector<T>& leaderchild = data[leader].child;
    auto it = std::find(leaderchild.begin(), leaderchild.end(), elem);
    if(it!=leaderchild.end())
        leaderchild.erase(it);
    else
        return false;

    // 3. 删除该元素
    data.erase(elem);

    return true;
}

template<class T>
void QuickUnion<T>::print(bool includeNewLine, bool includeSize, bool includeChild) const{
    for(auto it=data.begin();it!=data.end();it++){
        int elem = it->first;
        UnionNode<T> node = it->second;

        // 打印元素
        cout<<"["<<elem<<"]: ";

        // 打印leader
        cout<<node.leader<<' ';

        // 打印字节和数量
        if(includeSize){
            cout<<"("<<node.size<<")"<<' ';
        }

        // 打印子节点
        if(includeChild){
            int childSize = node.child.size();
            if(childSize){
                cout<<"{";
                for(int i=0;i<childSize;i++){
                    cout<<node.child[i]<<", ";
                }
                cout<<"\b\b} ";
            }
        }

        // 打印换行符
        cout<<(includeNewLine?'\n':' ');
    }
    cout<<endl;
}

namespace classTest{

    void test1(){
        // int arr[] = {0, 1, 1, 8, 8, 0, 0, 1, 8};
        // int len = 9;
        int arr[] = {0, 1, 9, 4, 9, 6, 6, 7, 8, 9};
        int len = sizeof(arr)/sizeof(arr[0]);
        bool includeSize = false, includeNewLine = false;
        // SeqUnion<int> s1(arr, len);
        QuickUnion<int> s2(arr, len); s2.print(true, true, true);
        s2.Union(3, 5); s2.print(true, true, true);

        s2.erase(4);
        s2.print(true, false, true);
    }

    void test2(){
        const int NUM = 3, SIZE = 4;
        int arr[][SIZE] = {{0, 2, 7}, {1, 5, 6}, {3, 4, 8, 9}};
        int len[NUM] = {3, 3, 4};
        int leader[NUM] = {0, 1, 8};
        QuickUnion<int> u;
        for(int i=0;i<NUM;i++){
            u.insert(arr[i], len[i], leader[i]);
        }
        u.print(true, true, true);

        u.erase(9);
        u.print(true, true, false);
    }

    void test3(){
        QuickUnion<int> u;
        // u.insert(2, 2);
        u.insert(1, 0);
        u.insert(1, 2);
        u.print();
    }
};

// int main(){
//     testExam::test1();
// }