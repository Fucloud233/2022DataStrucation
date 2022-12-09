#include<iostream>
using namespace std;

template<class T>
void print(T *arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i] <<' ';
    }
    cout<<endl;
}

void merge_sort(int *arr, int left, int mid, int right){
    int len = right - left + 1;
    int *temp = new int[len];
    int l = left, r = mid+1, k = 0;

    while(l<=mid&&r<=right){
        if(arr[l]<arr[r]){
            temp[k++] = arr[l++];
        }
        else{
            temp[k++] = arr[r++];
        }
    }

    while(l<=mid){
        temp[k++] = arr[l++];
    }

    while(r<=right){
        temp[k++] = arr[r++];
    }

    for(k=0;k<len;k++){
        arr[left+k] = temp[k];
    }
    delete temp;
}

void mergeSort(int *arr, int left, int right)
{
    if(left<right){
        int mid = (left+right)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge_sort(arr, left, mid, right);
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
    mergeSort(arr, 0, n-1);
    print(arr, n);
    delete arr;
}