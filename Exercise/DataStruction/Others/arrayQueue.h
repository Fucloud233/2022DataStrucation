#include<iostream>
#include"queue.h"

using namespace std;

template<class T>
class arrayQueue : public queue<T>
{
private:
	int theFront;
	int theBack;
	int arrayLength;
	T *queue;

public:
	arrayQueue(int intialCapacity = 10)
	{
		queue = new T[intialCapacity];
		arrayLength = intialCapacity;
		
		theFront = 0;
		theBack = 0;
	}
	
	~arrayQueue()
	{ 
		delete [] queue;
	}
	
	bool empty() const;
	
	int size() const;
	
	T& front();
	
	T& back();
	
	void pop();
	
	void push(const T& theElement);
	
	void print()
	{
		int i = (theFront + 1)%arrayLength;
		while(true)
		{	
			cout<<queue[i]<<' ';
			
			if(i==theBack)
				break;
			i = (i+1)%arrayLength;
		}
		
		cout<<endl;
	}
};

// theFront与theBack会留一个空位 
template<class T>
void arrayQueue<T>::push(const T& theElement)
{
	// 判断队列是否为满 
	if((theBack+1)%arrayLength==theFront)
	{
		T* newQueue = new T[2*arrayLength];
		int start = (theFront+1)%arrayLength;
		if(start<2)
			copy(queue+start, queue+start+arrayLength-1, newQueue);
		else
		{
			copy(queue+start, queue+arrayLength, newQueue);
			copy(queue, queue+theBack+1, newQueue+arrayLength-start);
		}
		
		theFront = 2*arrayLength-1;
		theBack = arrayLength - 2;
		arrayLength *= 2;
		queue = newQueue;
	}
	
	theBack = (theBack+1)%arrayLength;
	queue[theBack] = theElement;
}

template<class T>
bool arrayQueue<T>::empty() const
{
	return !(theFront==theBack);
}

template<class T>
void arrayQueue<T>::pop()
{
	// 判断队列是否为空 
	if(theFront == theBack)
	{
		cerr<<"The queue is empty!"<<endl;
		exit(0);
	}
		
	theFront = (theFront+1)%arrayLength;
	queue[theFront].~T();
} 

template<class T>
int arrayQueue<T>::size() const
{
	return arrayLength;
}


template<class T>
T& arrayQueue<T>::front()
{
	// 判断队列是否为空 
	if(theFront == theBack)
	{
		cerr<<"The queue is empty!"<<endl;
		exit(0);
	}
		
	return queue[theFront+1];
}

template<class T>
T& arrayQueue<T>::back()
{
	// 判断队列是否为空 
	if(theFront == theBack)
	{
		cerr<<"The queue is empty!"<<endl;
		exit(0);
	}
	
	return queue[theBack];	
}	
