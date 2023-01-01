#include <iostream>
using namespace std;

// m个水果 n个碟子
int solver(int m, int n){
    // 为记录数组分配空间
    int** arr;1
    arr = new int*[m+1];
    for(int i=0;i<=m;i++) {
        arr[i] = new int[n+1];
    }

    // 如果只有1个碟子 只有1种分法
    for(int i=0;i<=m;i++) {
        arr[i][1] = 1;
    }
    // 如果没有苹果 也只有1种分法
    for(int i=0;i<=n;i++) {
        arr[0][i] = 1;
    }

    for(int i=2;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            /*  碟子小于苹果
                1. 每个盘子都有梨 那就每个盘子放1个苹果
                2. 有1个盘没有梨 -> 不断递归 有梨的碟数不断减少
            */
            if(i<=j)
                arr[j][i] = arr[j-i][i] + arr[j][i-1];
            // 碟子大于苹果
            // 当碟子过多 对分水果没有影响
            else
                arr[j][i] = arr[j][j];
        }
    }

    return arr[m][n];
}

int main(){
    int t, m ,n;
    while(cin>> t){
        while(t--)
        {
            cin>>m >>n;
            cout<<solver(m, n)<<endl;
        }     
    }
}