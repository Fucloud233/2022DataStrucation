#include"queue.h"
#include"chain.h"

using namespace std;

template<class T>
class linkedQueueWithHeader: public queue<T>
{
private:
	Node<T>* queueFront;
	Node<T>* queueBack;
	int queueSize;

public:
	linkedQueueWithHeader(int intialCapacity = 10)
	{
		queueFront = new Node<T>(NULL, NULL);
		queueBack = queueFront;
		queueSize = 0;
	}
	
	~linkedQueueWithHeader()
	{
		Node<T> *tempNode = queueFront;
		
		while(tempNode!=NULL)
		{
			queueFront = queueFront->next;
			delete tempNode;
			tempNode = queueFront;
		}
		
		cout<<"Delete Over!"<<endl;
	}
	
	bool empty() const;
	
	int size() const;
	
	T& front();
	
	T& back();
	
	void pop();
	
	void push(const T&);
};

template<class T>
bool linkedQueueWithHeader<T>::empty() const
{
	return queueSize>0?true:false;
}

template<class T>
int linkedQueueWithHeader<T>::size() const
{
	return queueSize;
}

template<class T>
void linkedQueueWithHeader<T>::push(const T& elem)
{
	Node<T> *newNode = new Node<T>(elem, NULL);
	queueBack->next = newNode;
	queueBack = newNode;
	
	queueSize++;
}

template<class T>
void linkedQueueWithHeader<T>::pop()
{
	if(queueSize==0)
	{
		cerr<<"The linkedQueue is empty!"<<endl;
		exit(0);
	}
	else
	{
		Node<T> *tempNode = queueFront->next;
		queueFront->next = tempNode->next;	
		delete tempNode;
		
		queueSize--;
	}
}

template<class T> 
T& linkedQueueWithHeader<T>::front()
{
	return queueFront->next->elem;
}

template<class T> 
T& linkedQueueWithHeader<T>::back()
{
	return queueBack->elem;
}

int main()
{
	linkedQueueWithHeader<int> q;
	int n = 12;	
	
	
	for(int i=0;i<n;i++)
	{
		q.push(i);
		cout<<q.back()<<' ';
	}
	cout<<endl;
	

	for(int i=0;i<n;i++)
	{
		cout<<q.front()<<' ';
		q.pop();
	}
}


