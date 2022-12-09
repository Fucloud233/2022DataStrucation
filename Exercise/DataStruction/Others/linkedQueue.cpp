#include"queue.h"
#include"chain.h"

using namespace std;

template<class T>
class linkedQueue: public queue<T>
{
private:
	Node<T>* queueFront;
	Node<T>* queueBack;
	int queueSize;

public:
	linkedQueue(int intialCapacity = 10)
	{
		queueFront = NULL;
		queueSize = 0;
	}
	
	~linkedQueue()
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
bool linkedQueue<T>::empty() const
{
	return queueSize>0?true:false;
}

template<class T>
int linkedQueue<T>::size() const
{
	return queueSize;
}

template<class T>
void linkedQueue<T>::push(const T& elem)
{
	Node<T> *newNode = new Node<T>(elem, NULL);

	if(queueSize==0)
		queueFront = newNode;
	else
		queueBack->next = newNode;
	queueBack = newNode;
	
	queueSize++;
}

template<class T>
void linkedQueue<T>::pop()
{
	if(queueSize==0)
	{
		cerr<<"The linkedQueue is empty!"<<endl;
		exit(0);
	}
	else
	{
		Node<T> *tempNode = queueFront;
		queueFront = tempNode->next;	
		delete tempNode;
		
		queueSize--;
	}
}

template<class T> 
T& linkedQueue<T>::front()
{
	return queueFront->elem;
}

template<class T> 
T& linkedQueue<T>::back()
{
	return queueBack->elem;
}

int main()
{
	linkedQueue<int> q;
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


