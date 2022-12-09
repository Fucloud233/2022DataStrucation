#include<iostream>
#include<string>
using namespace std;

// 已知一棵二叉树的前序遍历和中序遍历结果，请写出这棵二叉树的后序遍历结果。

// using the index of string
void restoreTree1(const char* preArr, const char* inArr, int preBegin ,int preEnd, int inBegin){
    // 不存在节点
    if(preBegin>preEnd){
        return;
    }
    char center = preArr[preBegin];

    int len = 0;
    while(inArr[inBegin+len]!=center){
        len++;
    }
    
    restoreTree1(preArr, inArr, preBegin+1, preBegin+len, inBegin);
    restoreTree1(preArr, inArr, preBegin+len+1, preEnd, inBegin+len+1);
    cout<<center;
}

// directly use the subString
void restoreTree2(string preArr, string inArr){
    if(!preArr.size()){
        return;
    }
    char center = preArr[0];
    
    int len = 0;
    while(inArr[len]!=center){
        len++;
    }

    restoreTree2(preArr.substr(1, len), inArr.substr(0, len));
    restoreTree2(preArr.substr(len+1, preArr.size()), inArr.substr(len+1, inArr.size()));
    cout<<center;
}

int main(){
    string preArr, midArr;
    char enter;
    while(cin>>preArr>>midArr){
        int len = preArr.length();
        restoreTree1(preArr.c_str(), midArr.c_str(), 0, len-1, 0);
        // restoreTree2(preArr, midArr);
        cout<<endl;
    }
} 