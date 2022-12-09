#include<iostream>

using namespace std;

int main()
{
	int n, *arr;
	cin>>n;
	arr = new int[n];
	for(int i=0;i<n;i++)
		cin>>arr[i];
	
	//查找最大值和最小值
	int maxI = 0, minI = 0;
	for(int i=0;i<n;i++)
	{
		if(arr[i]>arr[maxI])
			maxI = i;
		if(arr[i]<arr[minI])
			minI = i;	
	} 
	
	cout<<arr[maxI]<<' '<<maxI+1<<endl;
	cout<<arr[minI]<<' '<<minI+1;
	
	return 0;
}
