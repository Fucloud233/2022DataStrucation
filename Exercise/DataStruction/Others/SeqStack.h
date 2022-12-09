#include<iostream>
#include "Stack.h"

using namespace std;

template<class T>
class SeqStack
{
private:
	
	T *data;
	int top, MAX_SIZE;

public:
	// 构造函数 
	SeqStack()
	{
		top = 0;
		MAX_SIZE = 100;
		data = new T[MAX_SIZE];
	}
	
	// 判断是否为空 
	bool empty() const 
	{
		if(top)
			return false;
		else
			return true;
	}
	
	int size() const
	{
		return top;
	}
	
	T& getTop() const
	{
		if(top<1)
			cerr<<"The Size is empty!"<<endl;
		T x = data[top-1];
		return x;
	}
	
	T& pop()
	{
		if(top<1)
			cerr<<"The Size is empty!"<<endl;
		T x = data[--top];
		return x;
	}
	
	
	void push(const T &elem)
	{
		if(top>=MAX_SIZE-1)
			cerr<<"Out of Size!"<<endl;
		data[top++] = elem;
	}
};
