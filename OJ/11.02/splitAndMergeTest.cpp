#include<iostream>
using namespace std;

void merge(int *arr, int begin, int mid, int end){
    int len = end - begin + 1;
    // 作为临时数组存储排序后的结果
    int *temp = new int[len];
    // 分别代表两个子数组的下标
    int l = begin, r = mid+1, k = 0;
    
    while(l<=mid&&r<=end){
        if(arr[r]<=arr[l]){
            temp[k++] = arr[r++];
        }
        else{
            temp[k++] = arr[l++];
        }
    }
    
    // 当右边的数组到头时 将左边的数组全部放入
    while(l<=mid){
        temp[k++] = arr[l++];
    }
    // 当左边的数组到头时 将右边的数组全部放入
    while(r<=end){
        temp[k++] = arr[r++];
    }
    
    for(int i=0;i<len;i++){
        arr[begin+i] = temp[i];
    }
    
    delete [] temp;
}

void split(int *arr, int begin, int end){
    // 当不可再拆分时 表示结束递归
    if(begin==end)
        return;
    
    int mid = (begin+end)/2;
    split(arr, begin, mid);
    split(arr, mid+1, end);
    merge(arr, begin, mid, end);
}

void print(int *arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}

int main(){

    int n, *arr;
    while(true){
        cin>>n;
        if(!n)
            return 0;
        
        arr = new int[n];
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }

        print(arr, n);
        split(arr, 0, n-1);
        print(arr, n);

        delete arr;
    }

}