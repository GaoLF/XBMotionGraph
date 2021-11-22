#include "TypeDefinition.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void split(const string& s, vector<string>& tokens, const string& delimiters)
{
	string::size_type lastPos = s.find_first_not_of(delimiters, 0);

	string::size_type pos = s.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));//use emplace_back after C++11 
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}

};

int GetRandomNum(int minv, int maxv)
{
	srand((unsigned)time(NULL));
	int value = rand() % (maxv - minv);
	value += minv;

	return value;
}

int GetRandomNum(int maxv)
{
	return GetRandomNum(0, maxv);
}