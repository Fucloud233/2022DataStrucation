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
        int largest = 0, temp = 0, l, r;
        while(true){
            l = (largest<<1) + 1;
            r = (largest<<1) + 2;
            if(l<i&&arr[l]>arr[largest]){
                largest = l;
            }
            if(r<i&&arr[r]>arr[largest]){
                largest = r;
            }

            if(largest!=temp){
                swap(arr[largest], arr[temp]);
                temp = largest;
            }
            else{
                break;
            }
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
        int largest = 0, temp = 0, l, r;
        while(true){
            l = (largest<<1) + 1;
            r = (largest<<1) + 2;
            if(l<i&&arr[l]<arr[largest]){
                largest = l;
            }
            if(r<i&&arr[r]<arr[largest]){
                largest = r;
            }

            if(largest!=temp){
                swap(arr[largest], arr[temp]);
                temp = largest;
            }
            else{
                break;
            }
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
    heapSort(arr, len, GREATER);
    print(arr, len);
    heapSort(arr, len, LESS);
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