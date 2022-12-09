#include<iostream>
using namespace std;

int quickSort(int *arr, int left, int right){
    int l = left+1, r = right;
    int mid = arr[left];
    while(l<r){
        while(arr[l]<mid&&l<=r){
            l++;
        }
        while(arr[r]>mid&&l<=r){
            r--;
        }

        // 当指针l和r发生交叉时 直接退出循环 而不要交换
        if(l<r&&arr[r]<arr[l])
            swap(arr[l],arr[r]);
        else
            break;
    }
    swap(arr[left], arr[r]);

    return r;
}

template<class T>
void print(T *arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i] <<' ';
    }
    cout<<endl;
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
    quickSort(arr, 0, n-1);
    print(arr, n);
    delete arr;
}