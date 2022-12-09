#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Node
{
public:
	int key;
	vector<Node*> forward;
	
	
	Node(int key, int level){
		this->key = key;
		forward.resize(level+1, NULL);
	}
}; 

class SkipList
{
private:
	int MAXLVL;
	float P;
	int level;
	Node *header;
	
	Node* createNode(int key, int level){
		Node *n = new Node(key, level);
		return n;
	}
	
	int randomLevel(){
		float r = (float)rand()/RAND_MAX;
		int lvl = 0;
		while(r<P && lvl<MAXLVL){
			lvl++;
			r = (float)rand()/RAND_MAX;;
		}
		
		return lvl;
	}

public:
	SkipList(int MAXLVL=4, float P=0.5){
		this->MAXLVL = MAXLVL;
		this->P = P;
		level = 0;
		header = new Node(-1, MAXLVL);
	}
	
	void insertElement(int key){
		Node *current = header;
		vector<Node*> update(MAXLVL+1, NULL);
		
		// ����һ���ݽ� 
		for(int i=level;i>=0;i--){
			// [����������1.��ͷNULL 2.��ԭ����] 
			while(current->forward[i]!=NULL && current->forward[i]->key<key){
				// ���ҵݽ� 
				current = current->forward[i];
			}
			 
			update[i] = current;
		}
		
		// �����µĽڵ�
		current = current->forward[0];
		if(current==NULL||current->key!=key){
			int rlevel = randomLevel();
			
			// ������ɵĽڵ���� ����Ҫ��ͷ���ȫ��ָ��ýڵ� 
			if(rlevel>level){
				for(int i=level+1;i<rlevel+1;i++){
					update[i] = header;
				}
				level = rlevel;
			}
			
			Node* n = createNode(key, rlevel);
			
			for(int i=0;i<=rlevel;i++){
				n->forward[i] = update[i]->forward[i];
				update[i]->forward[i] = n;
			}
			
			cout<<"Successfully Inserted key "<<key<<endl;
		}
	 
	}
	
	void deleteElement(int key){
		Node *current = header;
		vector<Node *> update(MAXLVL+1, NULL);
		
		// 1.���ҵ��ڵ�λ�� 
		for(int i=level;i>=0;i--){
			while(current->forward[i]!=NULL && current->forward[i]->key<key)
				current = current->forward[i];
			
			update[i] = current;
		}
		
		// 2.�жϽڵ��Ƿ���� ��ɾ���ڵ� 
		current = current->forward[0];
		if(current->key==key){
			for(int i=0;i<level;i++){
				// ��ֹɾ����ͷ 
				if(update[i]->forward[i]!=current)
					break;
				
				update[i]->forward[i] = current->forward[i];
			}
			
			while(level>0&&header->forward[level]==0)
				level--;
			
			cout<<"Successfully Deleted key "<<key<<endl;
		}
	}
	
	bool searchElement(int key){
		Node *current = header;
		
		for(int i=level;i>=0;i--){
			while(current->forward[i] && current->forward[i]->key<key)
				current = current->forward[i];
		}
		
		current = current->forward[0];
		if(current && current->key==key){
			cout<<"Found key: "<<key<<endl;
			return true;
		} 
		else
			return false;
	}
	
	void displayList()
	{
		Node *current = header;
		while(current->forward[0]){
			cout<<current->forward[0]->key<<' ';
			current = current->forward[0];
		}
		
		cout<<endl;
	}
};

int main()
{
	int arr[] {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
	int len = 10;
	
	SkipList list;
	for(int i=0;i<len;i++)
		list.insertElement(arr[i]);
	
	list.displayList();
	
	list.deleteElement(8);
	list.displayList();
	
	list.searchElement(2);
	list.searchElement(8);
}
