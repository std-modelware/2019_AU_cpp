#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vi;

	vi.push_back(10);
	vi.push_back(8);
	vi.push_back(1);

	cout << vi[0] << endl;
	cout << vi.at(1) << endl;
	cout << vi[2] << endl;

	cout << "----------" << endl;
	vi.pop_back();
	cout << vi[0] << endl;
	cout << vi[1] << endl;

	cout << "----------" << endl;
	vector<int>::iterator it = vi.erase(vi.begin());
	//cout << vi[0] << endl;
	cout << (*it) << endl;

}
