// β�ݹ�
#include<iostream>

using namespace std; 

// ����ÿһ������Ҫ���� 
int FibonacciRecursive(int n)
{
	if(n<2)
		return n;
	return (FibonacciRecursive(n-1)+FibonacciRecursive(n-2));
}

// ֻ�����һ������Ҫ���� 
int FibonacciTailRecursive(int n, int ret1, int ret2)
{
	if(n==0)
		return ret1;
	return FibonacciTailRecursive(n-1, ret2, ret1+ret2);
}

int main()
{
	cout<<FibonacciRecursive(5)<<endl;
	cout<<FibonacciTailRecursive(5, 0, 1)<<endl;
}
 
