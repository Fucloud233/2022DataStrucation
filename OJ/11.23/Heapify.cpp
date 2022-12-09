#include <iostream>
using namespace std;

enum HeapifyMode{
    BIG, SMALL
};

void print(int *arr, int len){
    for(int i=0;i<len;i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}

void bigRootHeapify(int *arr, int len){
    for(int i=1;i<len;i++){
        int later = i, pre = (i-1)/2;
        while(true){
            if(arr[later]>arr[pre]){
                swap(arr[later], arr[pre]);
            }
            else{
                break;
            }
            later = pre;
            pre = (later-1)/2;
        }

    }
}

void smallRootHeapify(int *arr, int len){
    for(int i=1;i<len;i++){
        int later = i, pre = (i-1)/2;
        while(true){
            if(arr[later]<arr[pre]){
                swap(arr[later], arr[pre]);
            }
            else{
                break;
            }
            later = pre;
            pre = (later-1)/2;
        }
    }  
}

void heapify(int *arr, int len, HeapifyMode mode){
    switch(mode){
        case BIG:
            bigRootHeapify(arr, len);
            break;
        case SMALL:
            smallRootHeapify(arr, len);
            break;
        default:
            cerr<<"[error] The mode of heapify is invalid!";
            break;
    }
}

// int main(){
//     // test();
//     // return 0;
//     int len;
//     cin>>len;
//     int* arr = new int[len];
//     for(int i=0;i<len;i++){
//         cin>>arr[i];
//     }
//     heapify(arr, len, BIG);
//     print(arr, len);
//     heapify(arr, len, SMALL);
//     print(arr, len);
// }
