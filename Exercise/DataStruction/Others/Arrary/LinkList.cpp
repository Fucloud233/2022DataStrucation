// #pragma once
#include "LinearList.h"
#include "Node.h"
#include <iostream>
using namespace std;

template<class T>
class LinkList: public LinearList<T>{
private:
    Node<T>* header;
    int listSize;
public:
    LinkList(int size=0);
    ~LinkList();

    void insert(int index, const T& elem);
    void erase(int index);

    T& get(int index) const;
    int indexOf(const T& theElement) const;
    void output(ostream& out) const;
    bool isEmpty() const;

    T& operator[](int index);
};

template<class T>
LinkList<T>::LinkList(int size){
    listSize = 0;
    header = new Node<T>(0, NULL);   
    
    Node<T>* p = header;
    for(int i=0;i<size;i++){
        p->next = new Node<T>(0, NULL);
        p = p->next;
    } 
}

template<class T>
LinkList<T>::~LinkList(){
    while(header){
        Node<T>* temp = header->next;
        delete header;
        header = temp;
    }
}

template<class T>
void LinkList<T>::insert(int index, const T& elem){
    // 注意在判断下标合法的时候 也要确定下界
    if(index<0||index>listSize){
        cerr<<"[Error] 下标越界 插入失败"<<endl;
        return;
    }
    // 找到对应位置上的指针
    Node<T>* p = header;
    for(int i=0;i<index;i++){
        p = p->next;
    }
    
    Node<T>* node = new Node<T>(elem, p->next);
    p->next = node;

    listSize++;
}

template<class T>
void LinkList<T>::erase(int index){
    if(index<0||index>listSize){
        cerr<<"[Error] 下标越界 删除失败"<<endl;
        return;
    }

    Node<T>* p = header;
    for(int i=0;i<index;i++){
        p = p->next;
    }

    Node<T>* temp = p->next;
    p->next = temp->next;
    delete temp;

    
    listSize--;
}

template<class T>
bool LinkList<T>::isEmpty() const{
    return !listSize;
}

template<class T>
T& LinkList<T>::get(int index) const{
    if(index<0||index>listSize){
        cerr<<"[Error] 下标越界 访问失败"<<endl;
        exit(-1);
        // return T();
    }

    Node<T>* p = header->next;
    for(int i=0;i<index;i++){
        p = p->next;
    }

    return p->elem;
}

template<class T>
int LinkList<T>::indexOf(const T& elem) const{
    Node<T>* p = header->next;
    int index = 0;
    while(p){
        if(p->elem==elem){
            return index;
        }
        index++;
        p = p->next;
    }

    return -1;
}

template<class T>
void LinkList<T>::output(ostream& out) const {
    Node<T>* p = header->next;
    while(p){
        cout<<p->elem<<' ';
        p = p->next;
    }
    cout<<endl;
}

namespace List{
    void test(){
        // 初始化数组
        LinkList<int> data;
        int arr[] = {3, 1, 4, 1, 5};
        int len = 5;
        for(int i=0;i<len;i++){
            data.insert(i, arr[i]);
        }
        data.output(cout);
        
        // 删除元素
        data.erase(2);
        data.output(cout);

        // 添加元素
        data.insert(4, 10);
        data.output(cout);

        cout<<data.get(3)<<endl;
        
    }  
};

int main(){
    List::test();
}