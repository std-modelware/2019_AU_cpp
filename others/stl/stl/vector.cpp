// элементы вектора копируютс€ в внутренний динамический массив

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{

	vector<int> vi;

	vi.push_back(10);
	vi.push_back(9);
	vi.push_back(8);

	std::cout << vi[0] << std::endl;
	std::cout << vi.at(1) << std::endl;
	std::cout << vi[2] << std::endl;

	//std::cout << vi[3] << std::endl;
	//std::cout << vi.at(3) << std::endl; // исключение


	// vi.insert(vi.begin() + 1, 100);

	std::cout << "===" << std::endl;
	std::cout << vi[0] << std::endl;
	std::cout << vi[1] << std::endl;
	std::cout << vi[2] << std::endl;


	vi.pop_back(); // удал€етс€ последний элемент, не возвраща€
	vector<int>::const_iterator pos = vi.erase(vi.begin() + 1); // удал€ет элемент и возвращает позицию следующего претендента
}
