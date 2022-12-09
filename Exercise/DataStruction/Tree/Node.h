#pragma once

#ifndef NULL
#define NULL 0
#endif

template<class T>
struct Node{
    T elem;

    Node();
    Node(const T& elem);
};

template<class T>
Node<T>::Node(){
    elem = T();
}

template<class T>
Node<T>::Node(const T& elem)
{
    this->elem = elem;
}