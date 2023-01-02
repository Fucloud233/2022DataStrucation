#include "LinearList.h"
#include <iostream>
using namespace std;

template<class T>
class SeqList: public LinearList<T> {
private:
    T* data;
    int num;
    int maxSize;
public:
    SeqList(int maxSize = 5);
    ~SeqList();

    void erase(int index);
    void insert(int index, const T& elem);

    T& get(int index) const;
    int indexOf(const T& elem) const;
    void output(ostream& out) const;

    bool isEmpty() const;
};

template<class T>
SeqList<T>::SeqList(int maxSize){

    this->maxSize = maxSize;
    this->num = 0;

    if(maxSize == 0){
        data = NULL;
    }
    else{
        data = new T[maxSize];
        for(int i=0;i<maxSize;i++){
            data[i] = T();
        }
    }
}

template<class T>
SeqList<T>::~SeqList(){
    delete [] data;
}

template<class T>
bool SeqList<T>::isEmpty() const {
    return !num;
}

template<class T>
T& SeqList<T>::get(int index) const{
    if(index>num){
        cerr<<"[Error] 下标越界 获取失败"<<endl;
    }

    return data[index];
}

template<class T>
int SeqList<T>::indexOf(const T& theElemet) const{
    for(int i=0;i<num;i++){
        if(data[i]==theElemet){
            return i;
        }
    }

    return -1;
}

template<class T>
void SeqList<T>::insert(int index, const T& elem) {
    if(index>num){
        cerr<<"[Error] 下标越界 插入失败"<<endl;
        return;
    }
    else if(num==maxSize){
        cerr<<"[Error] 数组满了 插入失败"<<endl;
        return;
    }
    else if(num==0){
        data[0] = elem;
    }

    for(int i=num;i>index;i--){
        data[i] = data[i-1];
    }
    data[index] = elem;
    num++;
}

template<class T>
void SeqList<T>::erase(int index){
    if(index>num){
        cerr<<"[Error] 下标越界 删除失败"<<endl;
        return;
    }
    else if(num==0){
        cerr<<"[Error] 数组为空 删除失败"<<endl;
        return;
    }

    for(int i=index;i<num;i++){
        data[i] = data[i+1];
    }
    num--;
}

template<class T>
void SeqList<T>::output(ostream& out) const {
    for(int i=0;i<num;i++){
        out<< data[i]<<' ';
    }
    out<<endl;
}

namespace List{
    void test(){
        // 初始化数组
        SeqList<int> data;
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
        
    }  
};

int main(){
    List::test();
}
