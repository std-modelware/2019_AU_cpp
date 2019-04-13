#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

template <class T>
class MyData {

private:
	T i;

public:
	MyData() {
		this->i = T();
	}

	MyData(T i) {
		this->i = i;
	}

	T getData() const {
		return this->i;
	}
};


int main()
{
	MyData<int> i0 = MyData<int>();
	MyData<int> i10 = MyData<int>(10);

	cout << "int " << i0.getData() << endl;
	cout << "int " << i10.getData() << endl;

	MyData<string> s0 = MyData<string>();
	MyData<string> s10 = MyData<string>("-10-");

	cout << "string " << s0.getData() << endl;
	cout << "string " << s10.getData() << endl;
}
