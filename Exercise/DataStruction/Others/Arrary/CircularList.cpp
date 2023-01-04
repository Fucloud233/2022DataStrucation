#include "LinkList.h"

// 通过修改普通的链表 以实现循环链表
template<class T>
class CircularLinkList: public LinkList<T>{
public:
    CircularLinkList(int size=0);
    CircularLinkList(T* left, T* right);

    int indexOf(const T& elem) const;
};  

// 注意这里 被const修饰的函数 还是能修改成员函数
// 不通过for循环也能实现数据的查找
template<class T>
int CircularLinkList<T>::indexOf(const T& elem) const{
    this->header->elem = elem;

    Node<T>* p = this->header->next;
    int index = 0;
    while(p->elem!=elem){
        p = p->next;
        index++;
    }

    return p==this->header ? -1 : index;
}

template<class T>
CircularLinkList<T>::CircularLinkList(int size){
    this->header = new Node<T>(0, NULL);
    this->header->next = this->header;
    this->listSize = size;

    Node<T>* p = this->header;
    for(int i=0;i<size;i++){
        p->next = new Node<T>(0, p->next);
    }
}

template<class T>
CircularLinkList<T>::CircularLinkList(T* left, T*right){
    this->header = new Node<T>(0, NULL);
    this->header->next = this->header;
    this->listSize = 0;

    Node<T>* p = this->header;
    for(T* i=left;i!=right;i++){
        p->next = new Node<T>(*i, p->next);
        p = p->next;

        this->listSize++;
    }
}

namespace List{
    void CircularTest(){
        int arr[] = {3, 1, 4, 1, 5};
        int len = 5;
        // LinkList<int> test(arr, arr+len);
        // cout<<test<<endl;

        CircularLinkList<int> list(arr, arr+len);
        cout<<list<<endl;
        cout<<list[5]<<endl;

        // Erase Test
        list.erase(4);  cout<<list<<endl;

        // Insert Test
        list.insert(4, 10); cout<<list<<endl;

        // operator[] Test
        // 循环链表不能这样直接访问 由于中间有个1 
        // cout<<list[8]<<endl;
        // cout<<list.get(8)<<endl;

        // indexOf Test
        cout<<"The indexOf "<<4<<" is " <<list.indexOf(4)<<endl;
    }
};


int main(){
    List::CircularTest();
    // List::test();
}
