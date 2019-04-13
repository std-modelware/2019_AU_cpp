#include "pch.h"
#include <iostream>
#include <list>

using namespace std;

int main()
{

	list<int> li;

	li.push_back(10);
	li.push_back(9);

	li.push_front(8);
	li.push_front(7);

	while (!li.empty()) {
		//std::cout << li.front() << std::endl;
		std::cout << li.back() << std::endl;
		//li.pop_front();
		li.pop_back();
	}
}
