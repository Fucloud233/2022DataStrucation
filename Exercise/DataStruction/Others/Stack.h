#include<iostream>

using namespace std;

template<class T>
class Stack
{
	public:
		virtual ~Stack() { }
		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual T& getTop() const = 0;
		virtual T& pop() = 0;
		virtual void push(const T& elem) = 0;
};

