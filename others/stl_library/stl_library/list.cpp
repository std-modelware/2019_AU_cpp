#include "pch.h"
#include <iostream>
#include <list>

using namespace std;

int main()
{
	list<int> vi;

	vi.push_back(10);
	vi.push_back(8);
	vi.push_back(1);

	for (list<int>::iterator it = vi.begin(); it != vi.end(); ++it) {
		cout << (*it) << endl;
	}

	cout << "----------" << endl;

	vi.push_front(11);

	for (list<int>::iterator it = vi.begin(); it != vi.end(); ++it) {
		cout << (*it) << endl;
	}

	cout << "----------" << endl;
	vi.pop_back();

	for (list<int>::iterator it = vi.begin(); it != vi.end(); ++it) {
		cout << (*it) << endl;
	}

	cout << "----------" << endl;
	list<int>::iterator it = vi.erase(vi.begin());

	for (list<int>::iterator it = vi.begin(); it != vi.end(); ++it) {
		cout << (*it) << endl;
	}

	cout << "----------" << endl;

	while (!vi.empty()) {
		//cout << vi.back() << endl;
		//vi.pop_back();
		cout << vi.front() << endl;
		vi.pop_front();

	}

}
