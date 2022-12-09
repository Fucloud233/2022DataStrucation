#include "BinaryTree.h"
#include <functional>

#define TreeNode BinaryTreeNode

enum Direct{
    RIGHT, LEFT
};

template<class T>
class BSTree: public BinaryTree<T>{
private:
    template<class CMP = greater<T>>
    TreeNode<T>* getBorder(TreeNode<T>* node, CMP cmp);

protected:
    // return the current node of the elem if existing or NULL
    TreeNode<T>* getNode(const T& elem);
    // return the parent node of parent
    // inclueSame!=true, when meeting same elem, it will return NULL
    TreeNode<T>* getParent(const T& elem, bool includeSame=true);
    Direct getDirect(TreeNode<T>* node, TreeNode<T>* parent) const;

public:
    BSTree();

    bool insert(const T& elem);
    void erase(const T& elem);
    bool search(const T& elem);
};

template<class T>
BSTree<T>::BSTree(){
    this->root = NULL;
}

template<class T>
Direct BSTree<T>::getDirect(TreeNode<T>* node, TreeNode<T>* parent) const{
    if(node==parent->left)
        return LEFT;
    else
        return RIGHT;
}

template<class T>
TreeNode<T>* BSTree<T>::getNode(const T& elem){
    TreeNode<T>* current = this->root;
    while(current){
        // less
        if(elem<current->elem){
            current = current->left;
        }
        // greater
        else if(elem>current->elem){
            current = current->right;
        }
        // equal
        else{
            return current;
        }
    }

    return NULL;
}

template<class T>
TreeNode<T>* BSTree<T>::getParent(const T& elem, bool includeSame){
    TreeNode<T>* current = this->root;
    TreeNode<T>* parent = NULL;
    while(current){
        // less
        if(elem<current->elem){
            parent = current;
            current = current->left;
        }
        // greater
        else if(elem>current->elem){
            parent = current;
            current = current->right;
        }
        // equal
        else {
            if(includeSame)
                break;
            else
                return NULL;
        }
    }

    return parent;
}

template<class T>
template<class CMP>
TreeNode<T>* BSTree<T>::getBorder(TreeNode<T>* node, CMP cmp){
    TreeNode<T>* current = node;
    if(!current){
        return NULL;
    }
    
    //find right border(max)
    if(cmp(1, 0)){
        while(current->right){
            current = current->right;
        }
    }
    else{
        while(current->left){
            current = current->left;
        }
    }
   
    return current;
}

template<class T>
bool BSTree<T>::insert(const T& elem){
    // the tree is NULL, insert directly
    if(!this->root){
        this->root = new TreeNode<T>(elem);
        return true;
    }
    
    // find the parent of the elem node
    TreeNode<T>* parent = getParent(elem, false);
    if(!parent){
        return false;
    }

    if(elem<parent->elem){
        parent->left = new TreeNode<T>(elem);
    }
    else if(elem>parent->elem){
        parent->right = new TreeNode<T>(elem);
    }
    else{
        return false;
    }

    return true;
} 

template<class T>
bool BSTree<T>::search(const T& elem){
    if(getNode(elem))
        return true;
    else
        return false;
}

template<class T>
void BSTree<T>::erase(const T& elem){
    TreeNode<T>* current = this->getNode(elem);
    if(!current)
        return;
    
    TreeNode<T>* parent = this->getParent(elem);
    TreeNode<T>* borderNode = NULL;

    // 1.left subTree
    if(!current->right){ 
        // find the min/max number in the subTree
        borderNode = getBorder(current->left, greater<T>());
    }
    // 2.right subTree
    else{
        borderNode = getBorder(current->right, less<T>());
    }

    // remove borderNode from its parent
    if(borderNode){
        TreeNode<T>* borderParent = getParent(borderNode->elem);
        if(getDirect(borderNode, borderParent))
            borderParent->left = borderNode->left;
        else
            borderParent->right = borderNode->right;

        borderNode->left = current->left;
        borderNode->right = current->right;
    }
    
    // remove current node
    if(!parent){
        this->root = borderNode;
    }
    else if(getDirect(current, parent)){
        parent->left = borderNode;
    }
    else{
        parent->right = borderNode;
    }

    delete current;
}

#include "../Assign.h"

namespace BSTTest{
    void insetTest(){
        // BSTree<int> tree1;
        // tree1.insert(0);
        // tree1.insert(0);
        // tree1.erase(0);
        // return;

        int arr[] = {3, 1, 4, 1, 5};
        int len = sizeof(arr)/sizeof(arr[0]);
        vector<int> data = getRandomArr(10, 50, 3);
        printArr(data);
        BSTree<int> tree;
        for(int i=0;i<data.size();i++){
            tree.insert(data[i]);
        }
        printArr(tree.orderTree(PRE));
        printArr(tree.orderTree(IN));

        // print("result", tree.search(3));
        // print("result", tree.search(5));
        // int num = getRandomNum();
        // print(num);
        // print("result", tree.search(num));

        // int num = getRandomNum();
        // erase elem one after another
        for(int i=0;i<data.size();i++){
            int num = data[i];
            print(string("After delete: ")+=to_string(num));
            tree.erase(num);
            printArr(tree.orderTree(LEVEL));
            // printArr(tree.orderTree(IN));
        }
    }

    void eraseTest(){
        int arr[] = {3, 1, 4, 5};
        int len = sizeof(arr)/sizeof(arr[0]);

        BSTree<int> tree;
        for(int i=0;i<len;i++){
            tree.insert(arr[i]);
        }
        print("InOrder: ");
        printArr(tree.orderTree(IN));
        
        int num = 4;
        print(string("After delete: ")+=to_string(num));
        tree.erase(num);
        printArr(tree.orderTree(IN));
    }
}