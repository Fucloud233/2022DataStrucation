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
	// ͷ�ڵ�����ָ������ �����洢���� 
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
		// ע����Ҫ��size�����޶� 
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
	// const��֤��������Ըı��Ա���� 
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
