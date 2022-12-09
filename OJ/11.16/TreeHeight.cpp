#include <iostream>
#include <map>
using namespace std;


int main(){
    int len, maxHeight = 1;
    map<int, int> Tree;
    cin>>len;
    for(int i=0;i<len-1;i++){
        int m, n;
        cin>>m>>n;

        // 初始化
        if(!i){
            Tree.insert(pair<int, int>(m, 1));
            Tree.insert(pair<int, int>(n, 2));
            maxHeight = 2;
            continue;
        }

        // n的层数是m的层数+1
        int height = Tree[m] + 1;
        Tree.insert(pair<int, int>(n, height));
        if(height>maxHeight){
            maxHeight = height;
        }
    }

    cout<<maxHeight<<endl;
}