#pragma once

#include "LinearList.h"
#include "Node.h"
#include <iostream>
using namespace std;

template<class T>
class LinkList: public LinearList<T>{
protected:
    Node<T>* header;
    int listSize;
public:
    LinkList(int size=0);
    LinkList(T* left, T* right);
    ~LinkList();

    void insert(int index, const T& elem);
    void erase(int index);
    void append(const LinkList<T>& list);
    void reverse();

    T& get(int index) const;
    int indexOf(const T& theElement) const;
    void output(ostream& out = cout) const;

    bool isEmpty() const;
    int size() const;

    T& operator[](int index);

    // 重载运算符 (此处必须声明该函数为模板函数 因为他不是成员函数)
    template<class Type>
    friend ostream& operator<<(ostream& out, const LinkList<Type>& list);
};

template<class T>
ostream& operator<<(ostream& out, const LinkList<T>& list){
    list.output(out);
    return out;
}

template<class T>
void LinkList<T>::reverse(){
    Node<T>* result = NULL;
    Node<T>* temp;

    while(header->next){
        temp = header->next;
        header->next = header->next->next;
        temp->next = result;
        result = temp;
    }

    header->next = result;
}

template<class T>
int LinkList<T>::size() const{
    return listSize;
}

template<class T>
LinkList<T>::LinkList(T* left, T* right){
    header = new Node<T>(T(), NULL);
    listSize = 0;

    Node<T>* cur = header;
    for(T* p=left;p!=right;p++){
        cur->next = new Node<T>(*p, NULL);
        
        cur = cur->next;
        listSize++;
    }
}

template<class T>
void LinkList<T>::append(const LinkList<T>& list){
    if(list.isEmpty()){
        return;
    }

    Node<T>* p = header;
    for(int i=0;i<listSize;i++){
        p = p->next;
    }
    
    Node<T>* cur = list.header->next;
    for(int i=0;i<list.listSize;i++){
        p->next = new Node<T>(cur->elem, NULL);
        p = p->next;
        cur = cur->next;
    }

    this->listSize += list.listSize;
}

template<class T>
LinkList<T>::LinkList(int size){
    listSize = 0;
    header = new Node<T>(T(), NULL);   
    
    Node<T>* p = header;
    for(int i=0;i<size;i++){
        p->next = new Node<T>(T(), NULL);
        p = p->next;
    } 
}

template<class T>
LinkList<T>::~LinkList(){
    for(int i=0;i<listSize;i++) {
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
    // 不能使用While循环 应修改为for循环
    // 在循环链表中 会出现死循环的现象
    for(int i=0;i<listSize;i++) {
        cout<<p->elem<<' ';
        p = p->next;
    }
    // cout<<endl;
}

template<class T>
T& LinkList<T>::operator[](int index){
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
        cout<<endl;
        
        // 删除元素
        data.erase(2);
        data.output(cout);
        cout<<endl;

        // 添加元素
        data.insert(4, 10);
        data.output(cout);

        cout<<data[3]<<endl;
        
        // 第二项测试
        cout<<"Second Test"<<endl;

        int arr2[] = {0, 1, 4, 2, 7, 5, 8};
        int len2 = 7;
        LinkList<int> data2(arr2, arr2+len2);
        data2.output(cout);
        cout<<"Size: "<<data2.size()<<endl;

        data.append(data2);
        data.output();

        data2.erase(3);
        data2.output();
        data.output();

        // 第三项测试
        data2.reverse();
        data2.output();
    }  
};

// int main(){
//     List::test();
// }