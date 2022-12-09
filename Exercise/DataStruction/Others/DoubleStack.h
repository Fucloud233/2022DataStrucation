#include<iostream>

using namespace std;

template<class T>
class DoubleStack
{
	public:
		T *data;
		int top1, top2, MAX_SIZE;
	
	public:
		DoubleStack()
		{
			MAX_SIZE = 100;
			data = new T[MAX_SIZE];
			top1 = 0;
			top2 = MAX_SIZE - 1;
		}
		
		bool empty() const
		{
			if(top1==0||top2==(MAX_SIZE-1))
				return true;
			else
				return false;
		}
		
		int size() const
		{
			int size = top1 + (MAX_SIZE-1-top2);
			return size;
		}
		
		T& getTop(int StackType) const
		{
			T x;
			if(StackType==1)
			{
				if(top1<=0)
				cerr<<"The Size is empty!"<<endl;
				x = data[top1-1];
			}
			else if(StackType==2)
			{
				if(top2>=MAX_SIZE-1)
				cerr<<"The Size is empty!"<<endl;
			x = data[top2+1];
			}
			return x;
		}
		
		T& pop(int StackType) 
		{
			T x;
			if(StackType==1)
			{
				if(top1<=0)
					cerr<<"The Size is empty!"<<endl;
				x = data[--top1];
			} 
			else if(StackType==2)
			{
				if(top2>=MAX_SIZE-1)
					cerr<<"The Size is empty!"<<endl;
				x = data[++top2];
			}
			return x;
		}
		
		void push(const T &elem, int StackType)
		{
			if(top2-top1==1)
			{	
				cerr<<"The Size is full!"<<endl;
				return;
			}
		
			if(StackType==1)
				data[top1++] = elem;
			else if(StackType==2)
				data[top2--] = elem;
		}
};
