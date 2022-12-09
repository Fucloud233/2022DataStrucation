#include<iostream>
#include<list> 

using namespace std;

int main()
{
	int n, count = 0, temp;
	int arr[500000] = {0};
	
	while(true){
		cin>>n;
		if(!n)
			break;
		
		for(int i=0;i<n;i++){
			cin>>arr[i];
		}
		
		
		for(int i=0;i<n-1;i++){
			for(int j=i+1;j<n;j++){
				if(arr[j]<arr[i])
					count++;
			}
		}
	
		cout<<count<<endl;
		
		count = 0;
	}
} 
