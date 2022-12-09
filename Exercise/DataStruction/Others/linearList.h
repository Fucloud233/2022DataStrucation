#include<iostream>

using namespace std;

template<class T>
class linearList
{
	public:
		virtual ~linearList(){};
		
		virtual bool isEmpty() const = 0;
		
		virtual T& get(int index) const = 0;
		
		virtual int indexOf(const T& theElement) const = 0;
		
		virtual void erase(int index) = 0;
		
		virtual void insert(int index, const T& elem) = 0;
		
		virtual void output(ostream& out) const = 0; 
};
