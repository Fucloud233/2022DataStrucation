#pragma once
#define NULL 0

template<class T>
struct binaryTreeNode{
    T elem;
    binaryTreeNode<T> *leftChild, *rightChild;

    binaryTreeNode(){
        leftChild = rightChild = NULL;
    }

    binaryTreeNode(const T& theElem){
        elem = theElem;
        leftChild = rightChild = NULL;
    }

    binaryTreeNode(const T& theElem, binaryTreeNode<T>* left, binaryTreeNode<T>* right){
        elem = theElem;
        leftChild = left;
        rightChild = right;
    }
};