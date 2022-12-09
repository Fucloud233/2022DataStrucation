#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

template<class T>
bool make2dArray(T ** &x, int numberOfRows, int numberOfColumns)
{
	try
	{
		x = new T * [numberOfRows];
		
		for(int i=0;i<numberOfColumns;i++)
			x[i] = new int [numberOfColumns];
		return true;
	}
	catch(bad_alloc)
	{
		return false;
	}
}

int main()
{
	srand(time(NULL));

	// 分配y数组的信息 
	int *y = new int;
	*y = 10;
	
	int len = 10;
	int *x = new int(len);
	
	for(int i=0;i<len;i++)
		*(x+i) = rand()%10;
	
	for(int i=0;i<len;i++)
		cout<<*(x+i)<<' ';
	cout<<endl;
	
	delete [] x; delete y;
	x = NULL; y = NULL;	
	
	//
	int n = 5;
	char (*c)[5];
	try
	{
		c = new char[n][5];
	}
	catch(bad_alloc)
	{
		cerr<<"Out of Memory"<<endl;
		exit(1);
	}	
}
