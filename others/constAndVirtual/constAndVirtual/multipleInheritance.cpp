#include "pch.h"
#include <iostream>

using namespace std;

class A1 {
public:
	A1() {
		cout << "A1::A1()" << endl;
	}

	void printA1() {
		cout << "A1::printA1()" << endl;
	}

	void print() {
		cout << "A1::print()" << endl;
	}

};

class A2 {
public:
	A2() {
		cout << "A2::A2()" << endl;
	}

	void printA2() {
		cout << "A2::printA1()" << endl;
	}

	void print() {
		cout << "A2::print()" << endl;
	}

};

class B : public A1, public A2 {
public:
	B() {
		cout << "B::B()" << endl;
	}

	void print() {
		A1::print();
		A2::print();
	}
};

int main()
{
	B b;
	b.printA1();
	b.printA2();
	b.print();
}
