// string.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	// строки в Си заканчиваются на 0
	char a[] = "Hello";
	char *b = a;
	char *c = &a[0];

	// строки в Си++ - string
	// работа как у базовых типов +,=, ==
	string *s1 = new string("Hello1");
	string s2 = "Hello2";

	// длина строки
	// посмотреть, как меняется capacity
	size_t sz = s1->size();

	// конкатенация
	string s3 = *s1 + s2;

	string s4 = *s1;

	cout << (s4 == *s1) << endl;

	string s5 = "Hello12";

	cout << (s5 == s2) << endl;

	s4 = s4 + "postfix";

	cout << s4 << endl;

	s5 = s4.substr(0, 3);

	string::size_type sst = s5.find(',');

	cout << (sst == string::npos) << endl;

	string::size_type sst1 = s5.find('l');

	cout << (sst1 == string::npos) << endl;

	cout << s5.empty() << endl;

	s5 = "hello";
	cout << s5 << endl;
	s5.replace(1, 2, "xxx");
	cout << s5 << endl;


	s5 = "hello";
	cout << s5 << endl;
	// string::npos = все символы до конца строки
	s5.replace(0, string::npos, "1x2");
	cout << s5 << endl;

	cout << s5.capacity() << endl;

	s5.reserve(s5.capacity() * 2);

	cout << s5.capacity() << endl;

	printf("%s\n", s5);
	printf("%s\n", s5.c_str());

	printf("%c\n", s5[1]);
	printf("%c\n", s5.at(1));


	// очистка строки
	s5 = "Hello";
	s5.clear();

	s5 = "Hello";
	s5.erase(2);


	s5 = "Hello1";

	s5 += "Hello2";

	s5.append("Hello3");

	s4 = "zzzz";
	s5.append(s4);

	// Один символ
	s5.push_back('l');

	string::size_type f = s5.find("zz");

}


// Задача: на входе текст, а на выходе распределение символов в этом тексте. Евгений Онегин
// Задача: на входе текст, а на выходе словарь (сколько разных слов в тексте). Евгений Онегин
// Задача: на входе текст, а на выходе список зеркальных слов, которые в прямом и обратном порядке одинаковы. Знаки препинания не учитывать.
// Задача: на входе текст, а на выходе список предложений, в которых имеется одно или несколько одинаковых слов, кроме союзов и частиц. Война и мир.