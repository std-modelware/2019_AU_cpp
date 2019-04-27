#include "pch.h"
#include <iostream>

using namespace std;

class A {
	const int intA;
public:
	A(int intA):intA(intA) {
		//this->intA = intA;
		cout << "A::A()" << endl;
		cout << "intA = " << this->intA << endl;
	}
};

int main()
{
	const int CONST_INT = 10;
    cout << "CONST_INT = " << CONST_INT << endl;

	cout << "-------" << endl;
	A a(303);
	
	cout << "-------" << endl;

	const int i = 50;
	const int * const pi = &i;

	const int j = 150;
	// pi = &j;

	cout << "i = " << i << endl;
	cout << "*pi = " << *pi << endl;

	cout << "-------" << endl;

	int z = 200;
	int * const pz = &z;

	cout << "*pz = " << *pz << endl;

	z = 400;

	cout << "*pz = " << *pz << endl;

}
