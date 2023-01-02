#include <iostream>
#include <sstream>
#include <string> 
#include "Node.h"
#include "linearList.h"

using namespace std;

template<class T>
class circularListWithHeader : public linearList<T>
{
protected:
	// 头节点用于指代链表 而不存储链表 
	Node<T> *headerNode;
	int listSize;
	
	void checkIndex(int index)
	{
		if(index<0||index>listSize)
		{
			ostringstream s;
			s<<"index = "<< index<<" size = "<< listSize;
			cerr<<s<<endl;
		}
	}

public:
	circularListWithHeader()
	{
		headerNode = new Node<T>();
		headerNode->next = headerNode;
		// 注意需要对size进行限定 
		listSize = 0;
	}
	
	bool isEmpty() const
	{
		if(listSize)
			return false;
		else
			return true;
	}
	
	int size() const
	// const保证函数不会对改变成员数据 
	{
		return listSize;
	}
	
	T& get(int index) const
	{
		checkIndex(index);
		
		Node<T> *p = headerNode;
		for(int i=0;i<index;i++)
			p = p->next;
		
		return *p;			
	}
	
	int indexOf(const T& elem) const
	{
		Node<T> *p = headerNode;
		for(int i=0;i<listSize;i++)
		{
			if(p->elem==elem)
				return i;
			p = p->next;
		}
	}
	
	void erase(int index)
	{
		checkIndex(index);
		
		Node<T> *p = headerNode, deleteNode = headerNode;
		
		if(index==0)
		{
			deleteNode = headerNode;
			headerNode = headerNode->next;
		}
		else
		{
			for(int i=0;i<index-1;i++)
				p = p->next;
			deleteNode = p->next;
			p->next = p->next->next;
		}
		
		delete deleteNode;
		listSize--;
	}
};

int main()
{
	return 0;
}
