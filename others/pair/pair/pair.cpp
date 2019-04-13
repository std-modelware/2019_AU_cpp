// pair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

class A {

public:
	A() {
		cout << "ctor" << endl;
	}

	~A() {
		cout << "dtor" << endl;
	}

};
int main()
{
	A *a = new A();

	try {
		//throw new exception("exception");
	}
	catch (...) {
		// забыл или выполнилось исключение
		cout << "catch" << endl;
		delete a;
	}
	delete a;
}

// 1. Класс на стеке
// 2. Логгирование конструктора и деструктора
// 3. Выброс исключения
// 4. Обработка искючения
// 5. Все то же, но с указателем
// ...