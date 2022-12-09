#pragma once
#include "Node.h"

#ifndef NULL
#define NULL 0
#endif

template<class T>
struct BinaryTreeNode: public Node<T>{
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;

    BinaryTreeNode(const T& elem = T());
    BinaryTreeNode(const T& elem, BinaryTreeNode<T>* left, BinaryTreeNode<T>* right);
};

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& elem){
    this->elem = elem;
    this->left = NULL;
    this->right = NULL;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& elem, BinaryTreeNode<T>* left, BinaryTreeNode<T>* right){
    this->elem = elem;
    this->left = left;
    this->right = right;
}

