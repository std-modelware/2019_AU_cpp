#include "pch.h"
#include <iostream>
#include <deque>

using namespace std;

int main()
{
	deque<int> vi;

	vi.push_back(10);
	vi.push_back(8);
	vi.push_back(1);

	cout << vi[0] << endl;
	cout << vi.at(1) << endl;
	cout << vi[2] << endl;

	cout << "----------" << endl;

	vi.push_front(11);

	cout << vi[0] << endl;
	cout << vi[1] << endl;
	cout << vi[2] << endl;
	cout << vi[3] << endl;

	cout << "----------" << endl;
	vi.pop_back();
	cout << vi[0] << endl;
	cout << vi[1] << endl;

	cout << "----------" << endl;
	deque<int>::iterator it = vi.erase(vi.begin());
	//cout << vi[0] << endl;
	cout << (*it) << endl;

}
