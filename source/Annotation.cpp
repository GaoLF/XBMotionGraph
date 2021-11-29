#include "Annotation.h"
#include <iostream>
#include <fstream>
#include "json/reader.h"
#include <string>
#include <cassert>
#include "Transition.h"
#include "Graph.h"
using namespace std;

XBKeyState::XBKeyState()
{
	start = 0;
	end = 0;
	action = ACTION_TYPE::IDLE;
}

XBKeyState::~XBKeyState()
{

}



XBAnnotation::XBAnnotation()
{
	TotalDuration = -1.f;
}

bool XBAnnotation::LoadJson(string filename)
{
	if (ParseJson(filename) == false)
	{
		cerr << "Failed to Parse Json!" << endl;
		return false;
	}

	if (TotalDuration > 0)
	{
		if (AddIdleState() == false)
		{
			cerr << "Failed to Add Idle State!" << endl;
			return false;
		}

		if (ConstuctStateMap() == false)
		{
			cerr << "Failed to Construct State Map!" << endl;
			return false;
		}

		if (SortStates() == false)
		{
			cerr << "Failed to Sort State!" << endl;
			return false;
		}
	}

	

	cout << "Succeed to Load Json without add idle: " << filename << endl;
	return true;
}

bool XBAnnotation::ParseJson(string filename)
{
	ifstream ifs;
	ifs.open(filename);
	//assert(ifs.is_open());

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
		cerr << "parse failed \n";
		return false;
	}

	Json::Value arrayObj = root["Annotations"];

	for (int i = 0; i < (int)arrayObj.size(); i++)
	{
		XBKeyState* newstate = new XBKeyState();
		newstate->start  = (float)arrayObj[i]["start"].asDouble();
		newstate->end    = (float)arrayObj[i]["end"].asDouble();
		string tmp_str   = arrayObj[i]["action"].asString();
		ACTION_TYPE tmp_action = ACTION_TYPE::IDLE;
		for (int j = 0; j < (int)ACTION_TYPE::ACTIONTYPENUM; j++)
		{
			if (tmp_str == Str_Action_Type[j])
			{
				tmp_action = (ACTION_TYPE)j;
			}
		}

		newstate->action = tmp_action;

		states.push_back(newstate);
	}

	ifs.close();
	return true;
}

bool XBAnnotation::AddIdleState()
{
	if (TotalDuration < 0)
	{
		cerr << "Warning: The Annotation's duration is not initialized." << endl;
		return false;
	}

	int length = (int)states.size();

	for (int i = 0; i < length; i++)
	{
		if (i == 0)
		{
			float tmp_start = states[0]->start;
			if (tmp_start > INTERVAL_2_IDLE)
			{
				XBKeyState* newstate = new XBKeyState();

				newstate->start = 0.f;
				newstate->end = tmp_start - INTERVAL_2_IDLE;
				newstate->action = ACTION_TYPE::IDLE;

				states.push_back(newstate);
			}
		}
		else
		{
			XBKeyState* pre_state = states[i - 1];
			if ((states[i]->start - states[i - 1]->end) > (INTERVAL_2_IDLE * 2))
			{
				XBKeyState* newstate = new XBKeyState();

				newstate->start = states[i - 1]->end + INTERVAL_2_IDLE;
				newstate->end = states[i]->start - INTERVAL_2_IDLE;
				newstate->action = ACTION_TYPE::IDLE;

				states.push_back(newstate);
			}
		}
	}

	//Supplement the last One
	if (length > 0)
	{
		float tmp_end = states[length - 1]->end;
		if (TotalDuration - tmp_end > INTERVAL_2_IDLE)
		{
			XBKeyState* newstate = new XBKeyState();

			newstate->start = states[length - 1]->end + INTERVAL_2_IDLE;
			newstate->end = TotalDuration;
			newstate->action = ACTION_TYPE::IDLE;

			states.push_back(newstate);
		}
	}

	return true;
}

bool XBAnnotation::ConstuctStateMap()
{
	int length = (int)states.size();
	for (int i = 0; i < length; i++)
	{
		if (states[i] != NULL)
		{
			ACTION_TYPE type = states[i]->action;
			if (StateMap.find(type) != StateMap.end())
			{
				StateMap[type].push_back(i);
			}
			else
			{
				vector<int> tmp;
				StateMap[type] = tmp;
				StateMap[type].push_back(i);
			}
		}
	}

	return true;
}

bool XBAnnotation::SortStates()
{
	if (TotalDuration < 0)
	{
		cerr << "Warning: The Annotation's duration is not initialized." << endl;
	}

	int length = (int)states.size();

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if ((j + 1) < length && states[j]->start > states[j]->end)
			{
				swap(states[j], states[j + 1]);
			}
		}
	}

	return true;
}

