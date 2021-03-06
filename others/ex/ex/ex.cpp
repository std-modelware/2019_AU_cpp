#include "pch.h"
#include <iostream>

using namespace std;

class myException : public exception {
public:
	myException(const char * message):exception(message){}
};

void printInt(int i) throw (myException) {
	cout << "i = " << i << endl;

	throw myException("something wrong!");

	cout << "i = " << i << endl;
	cout << "i = " << i << endl;
	cout << "i = " << i << endl;
}

int main()
{
	try {

		printInt(20);

	}
	catch (myException e) {
		cout << "catch (my):" << e.what() << endl;
	}
	catch (exception e) {
		cout << "catch:" << e.what() << endl;
	}
	catch (...) {
		cout << "catch" << endl;
	}
}
