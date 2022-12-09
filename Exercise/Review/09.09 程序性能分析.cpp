#include<iostream>

using namespace std;

// ranking 得分为 比其小的数+左边与他相等的 
template<class T> 
void rank(T arr[], int len, int result[])
{
	// 1. 初始化数组 
	for(int i=0;i<len;i++)
		result[i] = 0;
	
	// 2. 产生排名	
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<i;j++)
		{
			if(arr[j]<=arr[i])
				result[i]++;
			else
				result[j]++;
		}
	}
} 

template<class T>
void rearrange(T a[], int len, int r[])
{
	T *temp = new int[len];
	
	for(int i=0;i<len;i++)
		temp[r[i]] = a[i];
		
	for(int i=0;i<len;i++)
		a[i] = temp[i]; 
}

template<class T>
void printArr(T r[], int len)
{
	for(int i=0;i<len;i++)
			cout<<r[i]<<' ';
		cout<<endl;
}

// 选择排序 
template<class T>
void selectionSort(T arr[], int len)
{
	T min_num, min_index,  temp;
	for(int i=0;i<len;i++)
	{
		// 只要知道了index 就能知道数值 
//		min_num = arr[i];
		min_index = i;
		
		for(int j=i;j<len;j++)
			if(arr[j]<arr[min_index])
				min_index = j; 
		
		int temp = arr[i];
		arr[i] = arr[min_index];
		arr[min_index] = temp;
	}	
}

// 选择排序 改 
template<class T>
void selectionSort2(T arr[], int len)
{
	/* 当后续已经有序了 就不需要再进行找最大值了 */ 
	T min_num, min_index,  temp;
	bool sorted = false;
	for(int i=0;i<len&&!sorted;i++)
	{
		min_index = i;
		sorted = true;
		
		for(int j=i;j<len;j++)
		{
			if(arr[j]<arr[min_index])
				min_index = j;
			else
				sorted = false;
		}
			
		int temp = arr[i];
		arr[i] = arr[min_index];
		arr[min_index] = temp;
	}
}

// 冒泡排序 
template<class T>
void bubbleSort(T arr[], int len)
{
	for(int i=len;i>1;i--)
	{
		for(int j=0;j<i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

// 冒泡排序 改 
template<class T>
void bubbleSort2(T arr[], int len)
{
	// 当他不在排序时 可以提前终止排序 
	bool sorted = true;
	for(int i=len;i>1 && sorted;i--)
	{
		bool sorted = false;
		
		for(int j=0;j<i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				
				sorted = true;
			}
		}
	}
}

template<class T>
void swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

//原地重排
template<class T>
void rearrange2(T arr[], int len, T r[])
{
	for(int i=0;i<len;i++)
	{
		while(r[i]!=i)
		{
			int temp = r[i];
			swap(arr[i],arr[temp]);
			swap(r[i],r[temp]);			
		}
	}
} 
int main()
{
	const int len = 5;
	int arr[] = {4,3,9,3,7}, result[len];
	rank(arr,len,result);
	printArr(arr, len);
	rearrange(arr,len,result);
	printArr(arr, len);
	
	int arr1[] = {3,1,4,1,5};
//	selectionSort(arr1, len);
//	selectionSort2(arr1, len);
//	bubbleSort(arr1, len);
	bubbleSort2(arr1, len);
	printArr(arr1, len);
}
