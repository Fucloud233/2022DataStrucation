/*
    implement 4 order way of a basic tree
*/

#pragma once

#include "BinaryTreeNode.h"
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

enum orderMode {
    PRE, IN, POST, LEVEL
};

template<class T>
class BinaryTree{
protected:
    BinaryTreeNode<T> *root;

private:
    // create a tree in a way of preOrder
    void defaultPreRecursionCreate(BinaryTreeNode<T>* node, int& num, int deep);
    
    // order by recursion
    void preOrder(BinaryTreeNode<T>* node, vector<T> &result);
    void inOrder(BinaryTreeNode<T>* node, vector<T> &result);
    void postOrder(BinaryTreeNode<T>* node, vector<T> &result);

    // order by stack
    void preOrderStack(vector<T>& result);
    void inOrderStack(vector<T>& result);
    void postOrderStack(vector<T>& result);

public:
    BinaryTree(){
        root = NULL;
    }
    
    BinaryTree(int deep){
        int num = 1;
        this->root = new BinaryTreeNode<T>(num);
        defaultPreRecursionCreate(this->root, num, deep-1);
    }

    BinaryTree(T *data, int length);
    
    vector<T> levelOrder();
    vector<T> orderTree(orderMode mode);
    vector<T> orderTreeStack(orderMode mode);
    
};

template<class T>
BinaryTree<T>::BinaryTree(T* data, int length){
    // 如果为空直接返回
    if(!length){
        root = NULL;
        return;
    }

    //对队列进行初始化
    queue<BinaryTreeNode<T>*> q;
    root = new BinaryTreeNode<T>(data[0]);
    q.push(root);

    // 分别一次存储
    for(int i=1;i<length&&!q.empty();i++){
        
        BinaryTreeNode<T> *temp = q.front();
        q.pop();
        // 左子树
        if(data[i]){
            temp->left = new BinaryTreeNode<T>(data[i]);
            q.push(temp->left);
        }
        i++;

        //右子树
        if(data[i]){
            temp->right = new BinaryTreeNode<T>(data[i]);
            q.push(temp->right);
        }
    }
}

template<class T>
void BinaryTree<T>::defaultPreRecursionCreate(BinaryTreeNode<T>* node, int& num, int deep){
    // 已经达到给定层数 结束递归
    if(deep==0){
        return;
    }
    deep--;
    
    node->left = new BinaryTreeNode<T>(++num);
    defaultPreRecursionCreate(node->left, num, deep);

    node->right = new BinaryTreeNode<T>(++num);
    defaultPreRecursionCreate(node->right, num, deep);
}

// 前序遍历法
template<class T>
void BinaryTree<T>::preOrder(BinaryTreeNode<T>* node, vector<T> &result){
    if(!node){
        return;
    }

    result.push_back(node->elem);
    preOrder(node->left, result);
    preOrder(node->right, result);
}

// 中序遍历法
template<class T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T>* node, vector<T> &result){
    if(!node){
        return;
    }

    inOrder(node->left, result);
    result.push_back(node->elem);
    inOrder(node->right, result);
}

// 后续遍历法
template<class T>
void BinaryTree<T>::postOrder(BinaryTreeNode<T>* node, vector<T> &result){
    if(!node){
        return;
    }

    postOrder(node->left, result);
    postOrder(node->right, result);
    result.push_back(node->elem);
}

// 层级遍历法
template<class T>
vector<T> BinaryTree<T>::levelOrder(){
    vector<T> result(0);
    
    // if the tree is empty, return directly
    if(!root)
        return result;

    queue<BinaryTreeNode<T>*> queue;
    BinaryTreeNode<T>* node = root;

    while(true){
        // 遍历元素
        result.push_back(node->elem);

        // 分别将两个子树载入队列
        if(node->left){
            queue.push(node->left);
        }
        if(node->right){
            queue.push(node->right);
        }
        
        // 循环结束标志
        if(queue.empty()){
            break;
        }

        node = queue.front();
        queue.pop();
    }

    return result;

    // 需要对非空子树进行讨论 有点浪费时间
    // queue.push(root);
    
    // // 循环遍历
    // while(!queue.empty()){
    //     // 取出第一个元素
    //     node = queue.front();
    //     queue.pop();

    //     // 如果非空 则遍历 再将他的左右子树压入
    //     if(node){
    //         result.push_back(node->elem);
    //         queue.push(node->left);
    //         queue.push(node->right);
    //     }
    // }
}

template<class T>
vector<T> BinaryTree<T>::orderTree(orderMode mode){
    vector<T> result;
    
    switch(mode){
        case PRE:
            preOrder(root, result);
            break;
        case IN:
            inOrder(root, result);
            break;
        case POST:
            postOrder(root, result);
            break;
        case LEVEL:
            result = levelOrder();
            break;
        default:
            cerr<<"OrderMode ERROR!"<<endl;
            exit(-1);
    }

    return result;
}

template<class T>
void BinaryTree<T>::preOrderStack(vector<T>& result){
    stack<BinaryTreeNode<T>*> stack;
    stack.push(root);
    BinaryTreeNode<T>* node;

    while(!stack.empty()){
        node = stack.top();
        stack.pop();
        
        result.push_back(node->elem);
        if(node->right){
            stack.push(node->right);
        }
        if(node->left){
            stack.push(node->left);
        }
    }
}

template<class T>
void BinaryTree<T>::inOrderStack(vector<T>& result){
    stack<BinaryTreeNode<T>*> stack;
    BinaryTreeNode<T>* node = root;
    
    do{
        // 一直访问左节点
        while(node){
            stack.push(node);
            node = node->left;
        }

        if(!stack.empty()){
            // 返回根节点
            node = stack.top(); stack.pop(); 
            result.push_back(node->elem);
            // 访问右子树
            node = node->right;
        }
    }
    // 结束条件: 最右边的子树的为叶节点
    while(node!=NULL||!stack.empty());
}

// 用于记录左右方向
enum Tag {L, R};

template<class T>
struct stackNode{
    BinaryTreeNode<T> *ptr;
    Tag tag;
    stackNode(){
        ptr = NULL; tag = L;
    }

    stackNode(BinaryTreeNode<T> *node){
        ptr = node; tag = L;
    }
};

template<class T>
void BinaryTree<T>::postOrderStack(vector<T>& result){
    stack<stackNode<T>> stack;
    BinaryTreeNode<T>* node = root;
    stackNode<T> stkNode;

    do{
        // 一直访问左节点
        while(node!=NULL){
            stkNode.ptr = node; stkNode.tag = L;
            stack.push(stkNode);
            node = node->left;
        }
        
        bool isContinue = true;
        while(isContinue&&!stack.empty()){
            stkNode = stack.top(); stack.pop(); node = stkNode.ptr;
            switch(stkNode.tag){
            case L:
                stkNode.tag = R;
                stack.push(stkNode);
                isContinue = false;  
                node = node->right;                  
                break;
            case R:
                result.push_back(node->elem);
                break;
            }
        }
    }
    // 结束条件: 根节点
    while(!stack.empty());
}

template<class T>
vector<T> BinaryTree<T>::orderTreeStack(orderMode mode){
    vector<T> result;
    
    switch(mode){
        case PRE:
            preOrderStack(result);
            break;
        case IN:
            inOrderStack(result);
            break;
        case POST:
            postOrderStack(result);
            break;
        case LEVEL:
            result = levelOrder();
            break;
        default:
            cerr<<"OrderMode ERROR!"<<endl;
            exit(-1);
    }

    return result;
}
