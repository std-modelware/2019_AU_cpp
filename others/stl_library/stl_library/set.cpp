#include "pch.h"
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
	//set<int, greater<int> > vi;
	//set<string> vis;

	multiset<int, greater<int> > vi;
	multiset<string> vis;

	vi.insert(1);
	vi.insert(1);
	vi.insert(1);
	vi.insert(1);
	vi.insert(2);
	vi.insert(3);
	vi.insert(4);

	vis.insert("one");
	vis.insert("two");
	vis.insert("three");
	vis.insert("two");
	vis.insert("two");
	vis.insert("two");
	vis.insert("four");


	for (multiset<int>::iterator it = vi.begin(); it != vi.end(); ++it) {
		cout << (*it) << endl;
	}

	cout << "----------" << endl;

	for (multiset<string>::iterator it = vis.begin(); it != vis.end(); ++it) {
		cout << (*it) << endl;
	}

}
