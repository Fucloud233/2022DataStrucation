#include<iostream>

using namespace std;

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int n, *arr, num = 0;
	
	while(true){
		cin>>n;
		if(!n)
			break;
		
		arr = new int[n];
		for(int i=0;i<n;i++)
			cin>>arr[i];
		
		
		for(int i=0;i<n;i++){
			for(int j=1;j<n-i;j++){
				if(arr[j]<arr[j-1]){
					swap(arr[j], arr[j-1]);
					num++;
				}
			}
		}
		cout<<num<<endl;
		
		delete [] arr;
		num = 0;
	}
} 
