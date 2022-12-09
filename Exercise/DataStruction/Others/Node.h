template<class T>
struct Node{
	
	T elem;
	Node<T> *next;
	
	Node(){	}
	
	Node(const T& elem, Node<T>* next)
	{
		this->elem = elem;
		this->next = next; 
	}
};
