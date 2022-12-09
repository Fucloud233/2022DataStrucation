#include<iostream>
#include<sstream>
#include<string>

using namespace std;

template<class T>
class linearList
{
	public:
		virtual ~linearList(){};
		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual T& get(int theIndex) const = 0;
		virtual int indexOf(const T& theElement) const = 0;
		virtual void erase(int theIndex) = 0;
		virtual void insert(int theIndex, const T& theElement) = 0;
		virtual void output(ostream& out) const = 0;
};

template<class T>
class arrayList : public linearList<T>
{
	public:
		arrayList(int initialCapacity=10);
		arrayList(const arrayList<T> &);
		~arrayList() { delete []  element; }
		
		bool empty() const
		{
			return listSize == 0;
		}
		int size() const
		{
			return listSize;
		}
		T& get(int theIndex) const;
		int indexOf(const T& theElement) const;
		void erase(int theIndex);
		void insert(int theIndex, const T& theElement);
		void output(ostream& out) const;
	
		int capacity() const
		{
			return arrayLength;
		}
	private:
		void checkIndex(int theIndex) const;
		
		T* element;
		int arrayLength;	//一维数组的容量 	
		int listSize;
};

class illegalParameterValue
{
	public:
	    illegalParameterValue(string theMessage = "Illegal parameter value")
	    {
	        message = theMessage;
	    }
	    void outputMessage() { cout << message << endl; }
	private:
    	string message;
};

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
	if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    ListSize = 0;
}

template<class T>
arrayList<T>::arrayList(const T arrayList)
{
	
}

int main()
{
//	arrayList<int> temp(2);
}
