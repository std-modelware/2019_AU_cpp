#include "pch.h"
#include <iostream>
#include <set>

using namespace std;

int main()
{

//	set<int> si;
//	set<int, greater<int> > si;
	multiset<int> si;

	// смена порядка
	si.insert(4);
	si.insert(1);
	si.insert(3);
	si.insert(1);
	si.insert(1);
	si.insert(2);

	for (set<int>::const_iterator i = si.begin(); i != si.end(); i++)
	{
		std::cout << *i << std::endl;
	}
}
