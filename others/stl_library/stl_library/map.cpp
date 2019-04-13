#include "pch.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
	map<int, string> vi;

	vi[3] = "three";
	vi[2] = "two";
	vi[1] = "one";
	vi[4] = "four";

	vi.insert(make_pair<int, string>(0, "zero"));
	vi.insert(make_pair(-1, "minus one"));

	map<string, int> vir;
	vir["one"] = 1;
	vir["two"] = 2;
	vir["three"] = 3;
	vir["four"] = 4;

	vir.insert(make_pair("zero", 0));

	for (map<int, string>::iterator it = vi.begin(); it != vi.end(); ++it) {
		cout << (*it).first << "-" << (*it).second << endl;
	}

	cout << "----------" << endl;

	for (map<string, int>::iterator it = vir.begin(); it != vir.end(); ++it) {
		cout << (*it).first << "-" << (*it).second << endl;
	}

}
