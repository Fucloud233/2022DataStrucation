#include "heapify.cpp"
#include <iostream>
using namespace std;

enum SortMode{
    GREATER, LESS
};

void heapGreaterSort(int* arr, int len){
    for(int i=len-1;i>=1;i--){
        if(arr[0]>arr[i]){
            swap(arr[0], arr[i]);
        }
        else{
            continue;
        }
        int largest = 0, temp, l, r;

        // *最终目的就是判断根节点与左右子节点的大小关系 而不是子节点的关系 11.29
        while(true){
            l = (largest<<1) + 1;
            r = (largest<<1) + 2;
            if(l<i&&arr[l]>arr[r]){
                temp = l;
            }
            else if(r<i&&arr[r]>arr[l]){
                temp = r;
            }
            else{
                break;
            }

            if(arr[largest]<arr[temp]){
                swap(arr[largest], arr[temp]);
            }
            else{
                break;
            }
            largest = temp;
        }
    }
}

void heapLessSort(int* arr, int len){
    for(int i=len-1;i>=1;i--){
        if(arr[0]<arr[i]){
            swap(arr[0], arr[i]);
        }
        else{
            continue;
        }
        int largest = 0, temp, l, r;
        while(true){
            l = (largest<<1) + 1;
            r = (largest<<1) + 2;
            if(l<i&&arr[l]<arr[r]){
                temp = l;
            }
            else if(r<i&&arr[r]<arr[l]){
                temp = r;
            }
            else{
                break;
            }

            if(arr[largest]>arr[temp]){
                swap(arr[largest], arr[temp]);
            }
            else{
                break;
            }
            largest = temp;
        }
    }
}

void heapSort(int* arr, int len, SortMode mode = GREATER){
    heapify(arr, len, (HeapifyMode) mode);
    switch(mode)
    {
        case GREATER:
            heapGreaterSort(arr, len);
            break;
        case LESS:
            heapLessSort(arr,len);
            break;
        default:
            cerr<<"[error] The mode of heapify is invalid!";
            break;
    }
}

void test(){
    int len = 10;
    int arr[] = {2, 8, 4, 6, 1, 10, 7, 3, 5, 9};
    heapSort(arr, len);
    print(arr, len);
}

int main(){
    // test();
    // return 0;
    int len;
    cin>>len;
    int* arr = new int[len];
    for(int i=0;i<len;i++){
        cin>>arr[i];
    }
    heapSort(arr, len, GREATER);
    print(arr, len);
    heapSort(arr, len, LESS);
    print(arr, len);
}