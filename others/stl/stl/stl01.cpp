#include "pch.h"
#include <iostream>
#include <string>

class MyTypeInt {
private:
	int i;
public:
	MyTypeInt() {
		this->i = 0;
	}

	MyTypeInt(int i) {
		this->i = i;
	}

	int getData() const {
		return this->i;
	}

};

class MyTypeString {
private:
	std::string i;
public:
	MyTypeString() {
		this->i = "";
	}

	MyTypeString(std::string i) {
		this->i = i;
	}

	std::string getData() const {
		return this->i;
	}

};

int main()
{
	MyTypeInt i0 = MyTypeInt();
	MyTypeInt i10 = MyTypeInt(10);

	std::cout << i0.getData() << std::endl;
	std::cout << i10.getData() << std::endl;

	MyTypeString s0 = MyTypeString();
	MyTypeString s10 = MyTypeString("string");

	std::cout << s0.getData() << std::endl;
	std::cout << s10.getData() << std::endl;

}
