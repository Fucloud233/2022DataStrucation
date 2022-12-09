#include<iostream>

using namespace std;

int main()
{
	int n, *arr;
	cin>>n;
	arr = new int[n];
	for(int i=0;i<n;i++)
		cin>>arr[i];
	
	int current, rank = 1;
	cin>>current;
	for(int i=0;i<n;i++)
	{
		if(arr[i]>current)
			rank++;
	}
	cout<<rank;
}
