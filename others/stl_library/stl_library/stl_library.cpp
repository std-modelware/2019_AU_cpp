#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

class MyIntData {

private:
	int i;

public:
	MyIntData() {
		this->i = 0;
	}

	MyIntData(int i) {
		this->i = i;
	}

	int getData() const {
		return this->i;
	}
};

class MyStringData {

private:
	string i;

public:
	MyStringData() {
		this->i = "";
	}

	MyStringData(string i) {
		this->i = i;
	}

	string getData() const {
		return this->i;
	}
};

int main()
{
	MyIntData i0 = MyIntData();
	MyIntData i10 = MyIntData(10);

	cout << "int " << i0.getData() << endl;
	cout << "int " << i10.getData() << endl;

	MyStringData s0 = MyStringData();
	MyStringData s10 = MyStringData("-10-");

	cout << "string " << s0.getData() << endl;
	cout << "string " << s10.getData() << endl;
}
