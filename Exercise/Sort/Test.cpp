#include<iostream>
#include"ExchangeSort.h"
#include"InsertSort.h"
#include"MergeSort.h"

using namespace std;

int main(){
    int arr1[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int len = 10;
    quickSort(arr1, 0, len);
    print(arr1, len);
    return 0;

    // char *arr[] = {"bac", "abc", "bab"};
    // for(int i=1;i<3;i++){
    //     int j = i - 1;
    //     char *temp = arr[i];
    //     while(j>=0&&arr[j][0]>arr[i][0]){
    //         arr[j+1] = arr[j];
    //         j--;
    //     }
    //     arr[j+1] = temp;
    // }
    // print(arr, 3);


    // int arr1[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    // int len = 10;
    // print(arr1, len);
    // shellSort(arr1, len);
    // print(arr1, len);

    //  int arr2[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    // len = 10;
    // print(arr2, len);
    // mergeSort(arr2, 0, len-1);
    // print(arr2, len);
}