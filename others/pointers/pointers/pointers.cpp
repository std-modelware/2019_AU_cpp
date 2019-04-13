#include "pch.h"
#include <iostream>

using namespace std;

class A {

public:
	A() {
		cout << "A::ctor()" << endl;
	}

	~A() {
		cout << "A::dtor()" << endl;
	}
};

int main()
{
	A *a = new A();

	try {
		
		throw new exception("My exception");

	}
	catch (...) {
		cout << "exception catched" << endl;
		delete a;
		return 1;
	}

	delete a;
}
