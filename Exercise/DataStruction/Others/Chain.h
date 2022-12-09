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
		
	// 插入节点 
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
		
	//删除节点 
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
		
	// 链接链表 
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
		
	//倒转链表 
	void reverse()
	{
		Node<T> *result, *save;
		result = NULL;
			
		while(head)
		{
			//首先保留首节点以为的节点 
			save = head->next;
			//在第一个节点后面追加节点 
			head->next = result;
			//然后添加进结果链表中 
			result = head;
			//最后将剩余的节点送回原处 
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
		
	// 判断是否为空 
	bool isEmpty()
	{
		if(listSize==0)
			return true;
		else
			return false;
	}
		
	// 得到链表大小 
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
		
	// 打印数组 
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

