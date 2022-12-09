#include<iostream>
#include<math.h>
using namespace std;

void preOrder(int *arr, int len, int depth, int index){
    // 转换为真实坐标
    int currentIndex = (1<<(depth-1)) - 1 + index;

    if(currentIndex>len||!arr[currentIndex]){
        return;
    }
    
    // 访问数据
    cout<<arr[currentIndex]<<' ';
    
    // 遍历左右子树
    index <<= 1;
    preOrder(arr, len, depth+1, index);
    preOrder(arr, len, depth+1, index+1);
}

int main(){
    int loopNum;
    int data[1000] = {0};
    cin>>loopNum;
    for(int i=0;i<loopNum;i++){
        int temp = 0, len = 0;
        while(true){
            cin>>temp;
            if(temp==-1){
                break;
            }
            data[len++] = temp;
        }
        
        // 计算深度
        int depth = (int)(log(len)/log(2)) + 1;
        cout<<depth<<' ';

        // 顺序遍历
        preOrder(data, len, 1, 0);
        cout<<endl;
    }
}