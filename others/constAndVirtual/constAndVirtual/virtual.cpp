#include "pch.h"
#include <iostream>

using namespace std;

class Base {
public:
	Base() {
		cout << "Base::Base()" << endl;
	}

	virtual void vprint0() = 0;

	// overload
	void print() {
		cout << "Base::print()" << endl;
	}
	void print(int i) {
		cout << "Base::print(" << i << ')' << endl;
	}

	//override
	virtual void vprint() {
		cout << "Base::vprint()" << endl;
	}

	virtual ~Base() {
		cout << "Base::~Base()" << endl;
	}

};

class Derived : public Base {
public:
	Derived() {
		cout << "Derived::Derived()" << endl;
	}

	void print() {
		cout << "Derived::print()" << endl;
		Base::print(333);
	}

	void vprint() {
		cout << "Derived::vprint()" << endl;
	}

	virtual void vprint0() {
		cout << "Derived::vprint0()" << endl;
	}

	~Derived() {
		cout << "Derived::~Derived()" << endl;
	}

};

class Derived1 : public Base {
public:
	
	void vprint() {
		cout << "Derived1::vprint()" << endl;
	}

	virtual void vprint0() {
		cout << "Derived1::vprint0()" << endl;
	}

	~Derived1() {
		cout << "Derived1::~Derived1()" << endl;
	}

};

int main()
{
	//Base b;
	//b.print();
	//b.print(222);
	cout << "1------------" << endl;

	Derived d;
	d.print();
	// d.print(333);
	cout << "2------------" << endl;

	//Base *pB1 = new Base();
	//pB1->vprint();

	Derived *pD1 = new Derived();
	pD1->vprint();

	cout << "3------------" << endl;

	Base *pD2 = new Derived();
	pD2->vprint();

	cout << "4------------" << endl;

	Base *pD3 = new Derived1();
	pD3->vprint();

	cout << "5------------" << endl;

	pD2 = new Derived1();
	pD2->vprint();

	cout << "6------------" << endl;
	delete pD2;

	cout << "7------------" << endl;
	delete pD3;

	cout << "8------------" << endl;

}
