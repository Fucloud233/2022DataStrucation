#include <iostream>
#include "DoubleStack.h"
#include "SeqStack.h"

using namespace std;

int main()
{
	DoubleStack<int> ds;
	for(int i=0;i<7;i++)
	{
		ds.push(i,1+i%2);	
	} 
	
	for(int i=0;i<7;i++)
	{
		cout<<ds.pop(1+i%2)<<' ';
	}
	cout<<endl;


	// 顺序栈 
//	SeqStack<int> s;
//	for(int i=0;i<4;i++)
//		s.push(i);
//	
//	for(int i=0;i<4;i++)
//		cout<<s.pop()<<' ';
}
