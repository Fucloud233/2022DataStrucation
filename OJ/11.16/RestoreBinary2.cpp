#include<iostream>
#include<string>
#include<stdlib.h>
#include<string.h>
using namespace std;

struct Node
{
    char data;
    Node *left;
    Node *right;
};

Node *getBinaryTree(const char preOrder[], const char inOrder[], int len)
{
    if (preOrder == NULL || *preOrder == '\0' || len <= 0)
        return NULL;

    Node *root = new Node;
    root->data = *preOrder; // 前序遍历的第一个节点就是根节点

    // 找到根节点在中序遍历中的位置，其值也代表了左子树的节点数目
    int pos = 0;
    while (1)
    {
        if (*(inOrder + pos) == root->data)
        {
            break;
        }
        pos++;
    }

    // 递归找到左子树和右子树
    if (0 == pos)
    {
        root->left = NULL;
    }
    else
    {
        root->left = getBinaryTree(preOrder + 1, inOrder, pos);
    }

    if (0 == len - pos - 1)
    {
        root->right = NULL;
    }
    else
    {
        root->right = getBinaryTree(preOrder + pos + 1, inOrder + pos + 1, len - pos - 1);
    }

    return root;
}

void postOrder(Node *root)
{
    if (root == NULL)
        return;

    postOrder(root->left);
    postOrder(root->right);
    cout << root->data;
}

template<class T>
void restoreTree(T* preArr, T* midArr, int begin ,int end, int index){
    // 不存在节点
    if(begin>end){
        return;
    }
    // 只有一个节点
    else if(begin==end){
        cout<<preArr[begin];
        return;
    }

    T center = preArr[begin];
    int len = 0;
    while(midArr[index+len]!=center){
        len++;
    }
    
    restoreTree(preArr, midArr, begin+1, begin+len, index);
    restoreTree(preArr, midArr, begin+len+1, end, index+len+1);
    cout<<center;
}


int main(){
    string preArr, midArr;
    char enter;
    while(cin>>preArr>>midArr){
        int len = preArr.length();
        postOrder(getBinaryTree(preArr.c_str(), midArr.c_str(), len));
        cout<<endl;
        restoreTree(preArr.c_str(), midArr.c_str(), 0, len-1, 0);
        cout<<endl;
    }    
} 