#include "pch.h"
#include <iostream>

using namespace std;

template<class T>
class SP {
private:
	T *pointer;
public:
	SP():pointer(NULL) {
		// TODO:
	}

	SP(T *p):pointer(p) {
		// TODO:
	}

	operator T*() {
		// TODO:
		return pointer;
	}

	T* operator->() {
		// TODO:
		return pointer;
	}

	~SP() {
		// TODO:
	}
};

class MyClass {
public:
	MyClass() {
		cout << "MyClass::ctor" << endl;
	}

	~MyClass() {
		cout << "MyClass::dtor" << endl;
	}

	void print() {
		cout << "MyClass::print" << endl;
	}
};


void f(MyClass* m) {
	m->print();
}

int main()
{
	SP<MyClass> sp(new MyClass());
	f(sp);
	sp->print();
}
