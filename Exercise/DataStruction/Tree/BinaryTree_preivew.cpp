#include<iostream>
using namespace std;

enum orderMode {
    PRE, IN, POST
};

template<class T>
struct BinaryTreeNode{
    T elem;
    BinaryTreeNode<T> *leftChild, *rightChild;

    BinaryTreeNode(){
        leftChild = rightChild  = NULL;
    }

    BinaryTreeNode(const T& theElem){
        elem = theElem;
        leftChild = rightChild = NULL;
    }

    BinaryTreeNode(const T& theElem, BinaryTreeNode<T>* left, BinaryTreeNode<T>* right){
        elem = theElem;
        leftChild = left;
        rightChild = right;
    }
};

template<class T>
class BinaryTree{
private:
    BinaryTreeNode<T> *root;

    void create(BinaryTreeNode<T> *node, int& num, int deep){
        if(!deep)
            return;
        
        // 生成一个头结点
        if(!num){
            root = new BinaryTreeNode<T>(num);
            node = root;
        }
        deep--;

        // 生成左子树
        node->leftChild = new BinaryTreeNode<T>(++num);
        create(node->leftChild, num, deep);

        // 生成右子树
        node->rightChild = new BinaryTreeNode<T>(++num);
        create(node->rightChild, num, deep);
    }

    void preOrder(BinaryTreeNode<T> *tree){
        if(!tree){
            return;
        }

        cout<<tree->elem<<' ';
        preOrder(tree->leftChild);
        preOrder(tree->rightChild);
    }

    void inOrder(BinaryTreeNode<T> *tree){
        if(!tree){
            return;
        }

        inOrder(tree->leftChild);
        cout<<tree->elem<<' ';
        inOrder(tree->rightChild);
    }

    void postOrder(BinaryTreeNode<T> *tree){
        if(!tree){
            return;
        }

        postOrder(tree->leftChild);
        postOrder(tree->rightChild);
        cout<<tree->elem<<' ';
    }
public:
    BinaryTree(){
        root = NULL;
    }

    BinaryTree(int deep){
        int num = 0;
        create(root, num, deep); 
    }


    void order(int mode){
        
        switch(mode){
        case PRE:
            cout<<"PreOrder: ";
            this->preOrder(this->root);
            break;
        case IN:
            cout<<"InOrder: ";
            this->inOrder(this->root);
            break;
        case POST:
            cout<<"PostOrder: ";
            this->postOrder(this->root);
            break;
        }
        cout<<endl;
    }
};

int main(){
    BinaryTree<int> tree(1);
    tree.order(PRE);
    tree.order(IN);
    tree.order(POST);
}