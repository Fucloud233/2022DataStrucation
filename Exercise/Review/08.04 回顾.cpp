/* c++回顾 */

#include<iostream>
#include<stdlib.h>

using namespace std;

// 模板函数 
//template<class T>
//T abc(T a, T b, T c)
//{
//	if(a<=0 || b<=0 ||c<=0)
////		throw "All parameters should be > 0";
//			
//	return a + b * c;
//}

int abc(int a, int b, int c)
{
	if(a<=0 || b<=0 || c<=0)
		throw "All parameters should be > 0";
	return a + b * c;
}

int abc1(int a, int b, int c)
{
	if(a<0 & b<0 & c<0)
		throw 1;
	else if(a==0 & b==0 & c==0)
		throw 2;
	
	return a + b + c;
} 

// 常量引用不能修改值 
template<class T>
T abc1(const T &a, const T &b, const T &c)
{
	return a + b + c;	
} 

void swap(int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}

void swap1(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

double fuc(double x, double y)
{
	if(y==0)
		throw y;
	
	return x/y;
}

int main()
{	
//	int a=3, b=4, c=5;
	int a=-3, b=4, c=5;
//	cout<<"1: "<<abc(a,b,c)<<endl;
	cout<<"2: "<<abc1(a,b,c)<<endl;
	
	int x=3, y=4;
	swap(x,y);
	cout<<"swap: x="<<x<<" y="<<y<<endl;
	swap1(x,y);
	cout<<"swap1: x="<<x<<" y="<<y<<endl;
	
	cout<<endl;
	
//	double res;
//	try
//	{
//		res = fuc(2,3);
//		cout<<"The reuslt of x/y is:"<<res<<endl;
//		res = fuc(4,0);
//	}
//	catch(double)
//	{
//		cerr<<"error of dividing zero."<<endl;
//		exit(1);
//	}
	
//	try
//	{
//		int result = abc(2,0,4);
//		cout<<result<<endl;
//	}
//	// 跑出错误的信息变量类型要一致(char const*) 
//	catch(char const* e)
//	{
//		cout<<"The parameters to abc were 2, 0, and 4"<<endl;
//		cout<<"An exception has been throw"<<endl;
//		cout<<e<<endl;
//		return 1; 
//	}
	
	try
	{
		int result = 0;
		cout<<abc1(-1, -2, -3)<<endl;
		cout<<abc1(0, 0, 0)<<endl;
	}
	catch(int e1)
	{
		cout<<"Error "<<e1<<endl;
	}
	
} 
