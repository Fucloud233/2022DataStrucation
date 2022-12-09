#include<iostream>

using namespace std;

int arr[500000] = {0};
int temp[500000];
int count = 0;

void merge(int *arr, int left, int mid, int right){
	int i = left, j = mid+1, t = left;

	while (i <= mid && j <= right){
        if (arr[i] <= arr[j]){
            temp[t++] = arr[i++];
        }else{
        	count += j - t;
        	
            temp[t++] = arr[j++];
        }
    }
    while( i <= mid ) {
        temp[t++] = arr[i++];
    }
    while( j <= right ) {
        temp[t++] = arr[j++];
    }

	// 将排序后的数赋值回去 
	t = left;
	int tempLeft = left;
	while(tempLeft<=right){
		arr[tempLeft] = temp[t];
		t += 1;
		tempLeft += 1;
	}
}

void mergeSort(int *arr, int left, int right){
	if(left<right){
		int mid = (left+right)/2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid+1, right);
		merge(arr, left, mid, right);
	}
}

int main(){
	int n;
	
	while(true){
		cin>>n;
		if(!n)
			break;
		
		for(int i=0;i<n;i++){
			cin>>arr[i];
		}
		
		mergeSort(arr, 0, n-1);
		cout<<count<<endl;

		count = 0;
	}
}
