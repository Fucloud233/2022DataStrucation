#include<iostream>
using namespace std;

template<class T>
void print(T *arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i] <<' ';
    }
    cout<<endl;
}

int partition(int *arr, int left, int right){
    int l = left+1, r = right;
    int mid = arr[left];
    while(true){
        while(arr[l]<mid&&l<=r){
            l++;
        }
        while(arr[r]>mid&&l<=r){
            r--;
        }
        if(l<r&&arr[r]<arr[l])
            swap(arr[l],arr[r]);
        else
            break;
    }
    swap(arr[left], arr[r]);

    return r;
}

void quickSort(int *arr, int left, int right)
{
    if(left<right){
        int mid = partition(arr, left, right);
        quickSort(arr, left, mid-1);
        quickSort(arr, mid+1, right);
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
    quickSort(arr, 0, n-1);
    print(arr, n);
    delete arr;
}