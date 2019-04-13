// pair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

template<class T>
class SP {
	T *pointer;
public:
	SP(): pointer(NULL) {
		// TODO:
	}

	SP(T *p) {
		// TODO:
	}

	operator T*() {
		// TODO:
	}

	T* operator->() {
		// TODO:
	}

	~SP() {
	}

};

class MyClass {
public:
	void print() {
		cout << "print" << endl;
	}
};

void f(MyClass* m) {

}

int main()
{
	SP<MyClass> sp(new MyClass());
	f(sp);
	sp->print();
}