// ´òÓ¡³öÑî»ÔÈı½Ç 

#include<iostream>
#include"arrayQueue.h"

int main()
{
	arrayQueue<int> queue(100);
	queue.push(0);
	queue.push(1);
	queue.push(0);
	
	int previous = queue.front(), num = 12;
	
	queue.print();
	
	for(int i=0;i<num;i++)
	{
		while(1)
		{
			queue.push(previous+queue.front());
			previous = queue.front();
			queue.pop();
			
			if(queue.front()==0&&previous==0)
			{
				queue.push(previous);
				break;
			}
		}
		
		queue.print();
	}
}
