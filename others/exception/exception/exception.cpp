#include "pch.h"
#include <iostream>

using namespace std;

class myException : public exception {

};

class myException2 : public exception {

};

void func1(int i) { //throw(myException2, bad_exception) {
	cout << i << endl;
	throw myException2();
}


//class A {
//	int i;
//public:
//	A(int i = 0): i(i) {}
//	int getI() const { return this->i; }
//};

int main() throw(exception)
{

	try {
		func1(10);
	}
	catch (myException me) {
		cout << "catch myException" << endl;
	}
	catch (...) {
		cout << "catch" << endl;
	}
	//A *a = new A(10);
	//try {
	//	delete a;
	//	a = NULL;
	//	cout << "i = " << a->getI() << endl;
	//}
	//catch (exception e) {
	//	cout << "exception" << endl;
	//} 
	//finally 
	//{
	//	cout << "finally" << endl;
	//}
}

