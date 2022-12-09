// 尾递归
#include<iostream>

using namespace std; 

// 对于每一步都需要返回 
int FibonacciRecursive(int n)
{
	if(n<2)
		return n;
	return (FibonacciRecursive(n-1)+FibonacciRecursive(n-2));
}

// 只有最后一部才需要返回 
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
 
