#include "pch.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{

	map<int, string> mi;

	mi[3] = "three";
	mi[1] = "one";
	mi[2] = "two";
	mi[4] = "four";
	mi.insert(make_pair<int, string>(0, "zero"));
	mi.insert(make_pair(-1, "minus one"));

	for (map<int, string>::const_iterator i = mi.begin(); i != mi.end(); i++)
	{
		std::cout << (*i).first << " = " << (*i).second << std::endl;
	}
}
