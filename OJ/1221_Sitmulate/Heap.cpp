#include <iostream>
#include <vector>
using namespace std;

void Heapify(vector<int>& arr){
    for(int i=2;i<arr.size();i++){
        int index = i;
        while(index/2&&arr[index]>arr[index/2]){
            swap(arr[index], arr[index/2]);
            index /= 2;
        }
    }
}

int main(){
    vector<int> arr;
    arr.push_back(0);

    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int num;
        cin>>num;
        arr.push_back(num);
    }

    Heapify(arr);

    for(int i=1;i<arr.size();i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}