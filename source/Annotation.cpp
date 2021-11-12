#include "Annotation.h"
#include <iostream>
#include <fstream>
#include "json/reader.h"
#include <string>
#include <cassert>
using namespace std;

XBAnnotation::XBAnnotation()
{

}

bool XBAnnotation::LoadJson(string filename)
{
	ifstream ifs;
	ifs.open(filename);
	assert(ifs.is_open());

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
		cerr << "parse failed \n";
		return false;
	}
	Json::Value arrayObj = root["Annotations"];

	for (int i = 0; i < arrayObj.size(); i++)
	{
		XBKeyState* newstate = new XBKeyState();
		newstate->start  = (float)arrayObj[i]["start"].asDouble();
		newstate->end    = (float)arrayObj[i]["end"].asDouble();
		newstate->action = arrayObj[i]["action"].asString();

		states.push_back(newstate);
	}

	ifs.close();
	return true;
}
