#include<iostream>
#include "Node.h"

using namespace std;

template<class T>
class LinkList
{
protected:
	Node<T> *head;
	int listSize;

public:
	LinkList()
	{
		head = NULL;
		listSize = 0;
	}
		
	LinkList(int len)
	{
		head = NULL;
		for(int i=0;i<len;i++)
			insertNode(i+1,i);
		listSize = len;
	}
		
	// ����ڵ� 
	int insertNode(T elem, int index)
	{
		if(index<0||index>listSize)
			return -1;
			
		Node<T> *p = head;	
		if(index==0)
			head = new Node<T>(elem, p);
		else
		{
			for(int i=0;i<index-1;i++)
				p = p->next;
					
			p->next = new Node<T>(elem, p->next);
		}
		listSize++;
			
		return 1;
	}

	void push_back(T elem)
	{
		insertNode(elem, listSize);
	}
		
	//ɾ���ڵ� 
	int deleteNode(int index)
	{
		if(index<0||index>listSize)
			return -1;
			
		Node<T> *p = head, *delete_node = head;
			
		if(index==0)
			head = head->next;
		else
		{
			for(int i=0;i<index-1;i++)
				p = p->next;
				
				
			delete_node = p->next;
			p->next = delete_node->next;
		}
		listSize--;
		delete delete_node;
	}
		
	// �������� 
	int addList(LinkList<T> list)
	{
		if(list.isEmpty())
			return 0;
			
		Node<T> *p = head;			
		for(int i=0;i<listSize-1;i++)
		{
			p = p->next;
		}
			
		p->next = list.head;
		listSize += list.getSize();
	}
		
	//��ת���� 
	void reverse()
	{
		Node<T> *result, *save;
		result = NULL;
			
		while(head)
		{
			//���ȱ����׽ڵ���Ϊ�Ľڵ� 
			save = head->next;
			//�ڵ�һ���ڵ����׷�ӽڵ� 
			head->next = result;
			//Ȼ�����ӽ���������� 
			result = head;
			//���ʣ��Ľڵ��ͻ�ԭ�� 
			head =save;
		}
		head = result;
	}
		
	void createList(T *word)
	{
		int i = 0;
		while(*word)
			insertNode(*word++, i++);
	}
		
	// �ж��Ƿ�Ϊ�� 
	bool isEmpty()
	{
		if(listSize==0)
			return true;
		else
			return false;
	}
		
	// �õ�������С 
	int getSize()
	{
		return listSize;
	}
		
	Node<T>* getElem(int index)
	{
		if(index<0||index>listSize)
			exit(-1);
			
		Node<T> *p = head;	
			
		if(index==0)
			return p;
		else
		{
			for(int i=0;i<index;i++)
				p = p->next;
					
			return p;
		}
	}
		
	// ��ӡ���� 
	void printList()
	{
		if(listSize==0)
		{
			cout<<"NULL"<<endl;
			return;
		}
			
		Node<T> *p = head;
		for(int i=0;i<listSize;i++)
		{
			cout<<p->elem<<' ';
			p = p->next;
		}
		cout<<endl;
	}
};

