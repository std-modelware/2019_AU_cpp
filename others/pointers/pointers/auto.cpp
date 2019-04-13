#include "pch.h"
#include <iostream>
#include <memory>

using namespace std;

class B {
public:
	B() {
		cout << "b::ctor()" << endl;
	}

	~B() {
		cout << "b::dtor()" << endl;
	}

};

class A {
private:
	static int counter;
	int localName;
	auto_ptr<B> b;
public:
	A() {
		this->localName = A::counter++;
		this->b = auto_ptr<B>(new B());
		cout << "A::ctor(" << this->localName << ")" << endl;
	}

	~A() {
		//delete this->b;
		cout << "A::dtor(" << this->localName << ")" << endl;
	}

	void print() {
		cout << "print (" << this->localName << ")" << endl;
	}
};

int A::counter = 1;

void remove_auto_ptr(auto_ptr<A> a) {
	a->print();
}

auto_ptr<A> create_auto_ptr() {
	return auto_ptr<A>(new A());
}

int main()
{
	A sa;
	sa.print();

	auto_ptr<A> a1(new A());
	a1->print();

	auto_ptr<A> a2;
	a2 = a1;
	a2->print();

	auto_ptr<A> a3(a2);
	a3->print();
	remove_auto_ptr(a3);

	auto_ptr<A> a4;
	a4 = create_auto_ptr();

}
