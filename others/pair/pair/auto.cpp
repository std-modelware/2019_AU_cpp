// pair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>

using namespace std;

class B {
public:
	B() {
		cout << "B::ctor" << endl;
	}

	~B() {
		cout << "B::dtor" << endl;
	}

};

class A {
	static int counter;
	int localCounter;
	auto_ptr<B> b;
public:
	A() {
		this->localCounter = ++A::counter;
		cout << "ctor(" << this->localCounter << ")" << endl;
		this->b = auto_ptr<B>(new B());
	}

	~A() {
		//delete this->b;
		cout << "dtor(" << this->localCounter << ")" << endl;
	}

	void print() {
		cout << "print(" << this->localCounter << ")" << endl;
	}

};

int A::counter = 0;

void remove_auto_ptr(auto_ptr<A> a) {
	a->print();
}

auto_ptr<A> create_auto_ptr() {
	auto_ptr<A> a(new A);
	return a;
}

int main()
{
	A a_1;
	a_1.print();

	A a_2;
	a_2.print();

	A a_3;
	a_3.print();

	auto_ptr<A> a1(new A());
	// auto_ptr - �������� �������!!!
	// ��������� ������ ��������� ��� ������������ �������
	// �������� ++ �� ����������
	// ������������� ������ �� ��������
	// auto_ptr<A> a = new A();

	// ������� ������, �� ������� �� ���������
	// ��� � ����� ���������� auto �� ����� ���� ����������� ������ ������� - ��� ��������������� ������������
	// ���������� ����������� � �������� ������������ "��������" ���� ����� ��������

	// auto_ptr - � ������ ��� �������������� ������������� �����������

	auto_ptr<A> a2(a1);
	auto_ptr<A> a3 = a2;

	// ������������� auto : ����� ������ � �������
	remove_auto_ptr(a3);

	// ������� - �������� ������
	a1 = create_auto_ptr();

	try {
		a1->print();
		throw new exception("smth wrong!");
	}
	catch (...) {

	}
}

