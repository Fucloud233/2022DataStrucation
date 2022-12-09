#include <iostream>
#include "../Assign.h"
#include "BinaryTree.h"
using namespace std;

int main(){
    BinaryTree<int> tree(3);
    // vector<int> result = ;
    print(tree.orderTree(PRE));
    print(tree.orderTree(IN));
    print(tree.orderTree(POST));
    print(tree.orderTree(LEVEL));
}