/*
    create a AVL tree, and implement 4 rotate function.
    (rotateR, rotateL, rotateLR, rotateRL)
    the direction means that the node will move to.

    In the AVLTreeNode, BF = h_left - h_right
*/

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class AVLTreeNode{
public:
    T elem;
    // 平衡因子
    int bf;
    AVLTreeNode* parent;
    AVLTreeNode* left;
    AVLTreeNode* right;

    AVLTreeNode(const T& elem = T()){
        this->elem = elem;
        bf = 0;
        parent = left = right = NULL;
    }
};

template<class T>
class AVLTree{
private:
    AVLTreeNode<T>* root;

    // 找到对应位置上的父节点
    AVLTreeNode<T>* insertNewNode(const T& elem);
    
    void balance(AVLTreeNode<T>* parent);
    // 用于旋转树
    void RotateL(AVLTreeNode<T>* node);
    void RotateR(AVLTreeNode<T>* node);

    void inOrderFun(AVLTreeNode<T>* node, vector<T>& result);

public:
    AVLTree();
    // 插入节点
    bool insert(const T& elem);
    int height();
    vector<T> inOrder();
};

template<class T>
AVLTree<T>::AVLTree(){
    this->root = NULL;
}

// 如果不存在 返回父节点, 存在 返回NULL
template<class T>
AVLTreeNode<T>* AVLTree<T>::insertNewNode(const T& elem){
    
    // if tree is empty, insert directly
    if(!this->root){
        this->root = new AVLTreeNode<T>(elem);
        return NULL;
    }
    
    AVLTreeNode<T>* pos = root;
    AVLTreeNode<T>* parent = NULL;

    // find position of new Node
    while(pos){
        parent = pos;

        if(elem<pos->elem){
            pos = pos->left;
        }
        else if(elem>pos->elem){
            pos = pos->right;
        }
        // if element is existed, don't need insert repeatly
        else{
            return NULL;
        }
    }

    // insert following value
    if(elem<parent->elem){
        parent->left = new AVLTreeNode<T>(elem);
        pos = parent->left;
    }
    else{
        parent->right = new AVLTreeNode<T>(elem);
        pos = parent->right;
    }
    pos->parent = parent;

    return pos;
}

// 插入节点的函数
template<class T>
bool AVLTree<T>::insert(const T& elem){
    // 1. 找到位置进行插入
    AVLTreeNode<T>* pos = insertNewNode(elem);
    if(!pos)
        return true;

    // 2. 更新平衡因子
    AVLTreeNode<T>* parent = pos->parent;
    while(parent){
        if(pos==parent->left){
            parent->bf++;
            pos = parent;
        }
        else{
            parent->bf--;
            pos = parent;
        }
        
        // judge from the balance factor
        if(!parent->bf){
            break;
        }
        else if(parent->bf==2||parent->bf==-2){
            // 3. 重新调整平衡
            balance(parent);
            break;
        }

        parent = parent->parent;
    }
    
    return true;
}

template<class T>
void AVLTree<T>::balance(AVLTreeNode<T>* parent){
    // the ndoe in the left
    if(parent->bf>0){
        if(parent->left->bf>0)
            this->RotateR(parent);
        else{
            this->RotateL(parent->left);
            this->RotateR(parent);
        }
    }
    // the node in the right
    else{
        if(parent->right->bf<0)
            this->RotateL(parent);
        else{
            this->RotateR(parent->right);
            this->RotateL(parent);
        }
    }
}

// we use the direction of rotating to define the function
// right rotate
template<class T>
void AVLTree<T>::RotateR(AVLTreeNode<T>* node){
    // get the node of y
    AVLTreeNode<T>* current = node->left;

    // exchange step 1: exchange the position both of x and y
    AVLTreeNode<T>* parent = node->parent;
    if(parent){
        if(parent->left==node)
            parent->left = current;
        else
            parent->right = current;
    }
    else{
        root = current;
    }
    current->parent = parent;

    // exchange step 2: changge the child node 
    // (only the mid node should be changed)
    node->left = current->right;
    if(node->left)
        node->left->parent = node; // 改变根节点
    
    // exchange step 3: make x after y
    current->right = node; 
    node->parent = current;     // 改变根节点

    node->bf -= 1 + max(0, current->bf);
    current->bf -= 1 - min(0, node->bf);
}

template<class T>
void AVLTree<T>::RotateL(AVLTreeNode<T>* node){
    // 交换x 和 a
    AVLTreeNode<T>* current = node->right;

    AVLTreeNode<T>* parent = node->parent;
    if(parent){
        if(parent->left==node)
            parent->left = current;
        else
            parent->right = current;
    }
    else{
        root = current;
    }
    current->parent = parent;

    // 交换x和a的子节点
    node->right = current->left; 
    if(node->right)
        node->right->parent = node; // 改变根节点
    
    current->left = node; 
    node->parent = current;             // 改变根节点

    node->bf += 1 - min(0, current->bf);
    current->bf += 1 + max(0, node->bf);
}

// 递归遍历
template<class T>
void AVLTree<T>::inOrderFun(AVLTreeNode<T>* node, vector<T>& result){
    if(!node)
        return;
    
    this->inOrderFun(node->left, result);
    result.push_back(node->elem);
    this->inOrderFun(node->right, result);
}

// 得到中序遍历后的数组
template<class T>
vector<T> AVLTree<T>::inOrder(){
    vector<T> result(0);
    if(!root){
        cerr<<"[Error] The AVLTree is empty!"<<endl;
        return result;
    }

    this->inOrderFun(root, result);
    return result;
}

template<class T>
int AVLTree<T>::height(){
    int height = 0;
    AVLTreeNode<T>* current = root;
    while(current){
        height++;

        if(current->bf>0){
            current = current->left;
        }
        else{
            current = current->right;
        }
    } 

    return height;
}

template<class T>
void print(vector<T> arr){
    for(auto it=arr.begin();it!=arr.end();it++){
        cout<<*it<<' ';
    }
    cout<<endl;
}

#include <stdlib.h>

namespace testFun{
    void AVLTreeTest(){
        srand(100);
        // int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
        // int arr[] = {1, 2, 3, 4, 5};
        // int len = 5;
        // int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15, 1, 5, 12, 20};
        // int arr[] = {5, 2, 6, 1, 3, 4};
        int len = 100;
        AVLTree<int> tree;
        vector<int> testData;
        for(int i=0;i<len;i++){
            // tree.insert(arr[i]);
            int data = rand()%30;
            tree.insert(data);
            testData.push_back(data);
        }
        print(testData);
        print(tree.inOrder());
        cout<<tree.height()<<endl;
    }
}

int main(){
    // testFun::AVLTreeTest();
    // return 0;
    int n = 0, temp = 0;        
    cin>>n;
    AVLTree<int> tree;
    for(int i=0;i<n;i++){
        cin>>temp;
        tree.insert(temp);
    }

    // ouput result
    cout<<tree.height()<<endl;
    vector<int> inOrderArr = tree.inOrder();
    print(inOrderArr);
}
