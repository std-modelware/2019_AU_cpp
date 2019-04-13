#include "pch.h"
#include <iostream>
#include <string>

template <class T>
class MyTypeData {
private:
	T i;
public:
	MyTypeData() {
		this->i = T();
	}

	MyTypeData(T i) {
		this->i = i;
	}

	T getData() const {
		return this->i;
	}

};


int main()
{
	MyTypeData<int> i0 = MyTypeData<int>();
	MyTypeData<int> i10 = MyTypeData<int>(10);

	std::cout << i0.getData() << std::endl;
	std::cout << i10.getData() << std::endl;

	MyTypeData<std::string> s0 = MyTypeData<std::string>();
	MyTypeData<std::string> s10 = MyTypeData<std::string>("string");

	std::cout << s0.getData() << std::endl;
	std::cout << s10.getData() << std::endl;

}
