// �������� ������� ���������� � ���������� ������������ ������

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
	//std::cout << vi.at(3) << std::endl; // ����������


	// vi.insert(vi.begin() + 1, 100);

	std::cout << "===" << std::endl;
	std::cout << vi[0] << std::endl;
	std::cout << vi[1] << std::endl;
	std::cout << vi[2] << std::endl;


	vi.pop_back(); // ��������� ��������� �������, �� ���������
	vector<int>::const_iterator pos = vi.erase(vi.begin() + 1); // ������� ������� � ���������� ������� ���������� �����������
}
