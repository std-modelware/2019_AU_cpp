#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	// C-строки
	char a[] = "Hello";
	char *b = &a[0];
	char *c = a;

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;

	string s1 = "Hello1";
	string *s2 = new string("Hello2");

	string s3 = s1 + *s2;

	string s5 = *s2;
	cout << (s5 == *s2) << endl;

	//	cout.operator<<(s5 == *s2).operator<<(endl);

	cout << s5 << endl;
	cout << *s2 << endl;

	s5 += "3";

	cout << s5 << endl;
	cout << *s2 << endl;

	cout << (s5 == *s2) << endl;

	s5.append("1sssss1");
	s5 += ("2sssss2");
	s5.push_back('3');
	s5.append("1sssss11sssss11sssss1");

	cout << s5 << endl;

	string::size_type s5_len = s5.length();

	string::size_type s5_find_s = s5.find('s');

	cout << s5[8] << endl;
	cout << s5.at(8) << endl;

	string::size_type s5_find_s_ = s5.find('$');

	cout << (s5_find_s_ == string::npos) << endl;


	//s5.clear();
	s5.erase();
}
