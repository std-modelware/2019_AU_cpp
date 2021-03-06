#include "pch.h"
#include <iostream>

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

	int getInt() const {
		return this->i;
	}

};

int main()
{
	MyTypeInt i0 = MyTypeInt();
	MyTypeInt i10 = MyTypeInt(10);

	std::cout << i0.getInt() << std::endl;
	std::cout << i10.getInt() << std::endl;

}
