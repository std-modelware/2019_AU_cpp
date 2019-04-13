#include "pch.h"
#include <iostream>
#include <deque>

using namespace std;

int main()
{

	deque<int> di;

	di.push_back(10);
	di.push_back(9);
	
	di.push_front(8);
	di.push_front(7);

	std::cout << di[0] << std::endl;
	std::cout << di.at(1) << std::endl;
	std::cout << di[2] << std::endl;
	std::cout << di.at(3) << std::endl;
}
