#include<iostream>
using namespace std;

void TreeDeepFind(int*arr, int n, int depth){
    int start  = 1, len = 1;
    start = (start<<(depth-1)) - 1;
    len = len<<(depth-1);

    if(start>n){
        cout<<"EMPTY"<<endl;
        return;
    }

    for(int i=start;i<start+len&&i<n;i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}

int main(){
    int n, depth;
    int *arr;
    while(true){
         cin>>n;
        if(!n)
            break;

        arr = new int[n];
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        cin>>depth;

        TreeDeepFind(arr, n, depth);
    }
}