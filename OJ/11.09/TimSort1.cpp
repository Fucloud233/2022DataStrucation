#include<iostream>
using namespace std;

template<class T>
void print(T *arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i] <<' ';
    }
    cout<<endl;
}

void translate(int *arr, int n){
    int i = 0, first, last;
    bool isFirst = false;
    
    while(i<n){
        // 跳过正序序列
        while(arr[i]<=arr[i+1]&&i+1<n){
            i++;
            isFirst = true;
        }

        // 1. 如果是正序开始 需要跳过
        // 2. 如果从逆序开始 则不要跳过
        if(isFirst)
            ++i;
        
        // 跳过逆序序列
        first = i;
        while(arr[i]>=arr[i+1]&&i+1<n){
            i++;
        }
        last = i;
        

        if(last != first){
            while(last>=first){
                swap(arr[first++], arr[last--]);
            }
            i++;
        }
       
        isFirst = false;
    }
}

int main()
{
    int n = 5;
    int *arr;

    cin>>n;
    arr = new int[n];
    
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    translate(arr,n);
    print(arr, n);
    delete arr;
}