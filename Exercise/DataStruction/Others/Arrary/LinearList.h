#pragma once
#include <iostream>
using namespace std;

template<class T>
class LinearList {
public:
	// virtual ~LinearList(){};

	// 操作函数
	virtual void erase(int index) = 0;
	virtual void insert(int index, const T& elem) = 0;
	// 获取函数
	virtual T& get(int index) const = 0;
	virtual int indexOf(const T& theElement) const = 0;
	virtual void output(ostream& out) const = 0; 
	// 状态函数
	virtual bool isEmpty() const = 0;
};
