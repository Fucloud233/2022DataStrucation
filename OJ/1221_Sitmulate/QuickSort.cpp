#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& arr, int begin, int end){
    int key = arr[begin];
    int left = begin, right = end;

    while(left<right){
        while(arr[right]>=key&&left<right){
            right--;
        }
        swap(arr[left], arr[right]);

        
        while(arr[left]<=key&&left<right){
            left++;
        }
        swap(arr[left], arr[right]);
    }

    return left;    
}

void quickSort(vector<int>& arr, int begin, int end){
    if(begin>=end){
        return;
    }

    int mid = partition(arr, begin, end);
    quickSort(arr, 0, mid-1);
    quickSort(arr, mid+1, end);
}

int main(){
    vector<int> arr;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int num;
        cin>>num;
        arr.push_back(num);
    }

    quickSort(arr, 0, arr.size()-1);

    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}