#ifndef _ANNOTATION_H
#define _ANNOTATION_H

//Make the Annotation Decoupled with the frame info.
//标注信息里只有时间标记，与帧信息解耦
//Animation类与时间和帧都关联

#include <string>
#include <vector>
#include <map>
#include "TypeDefinition.h"

class XBKeyState
{
public:
	XBKeyState();
	~XBKeyState();

public:
	float start;
	float end;
	ACTION_TYPE action;
};

class XBAnnotation
{
public:
	//Primary Function
	XBAnnotation();

	//Public Function
	std::vector<XBKeyState*> GetStates()
	{
		return states;
	}

	XBKeyState* GetState(int index)
	{
		if (index < (int)states.size())
			return states[index];
		else
			return new XBKeyState();
	}

	void SetStates(std::vector<XBKeyState*>& value)
	{
		states = value;
	}

	void SetTotalDuration(float value)
	{
		TotalDuration = value;
	}

	float GetTotalDuration()
	{
		return TotalDuration;
	}

	bool LoadJson(std::string filename);

	//By default the annotation does not annotated with idle state
	bool AddIdleState();

	bool ConstuctStateMap();

	std::vector<int>& FindArrayofType(ACTION_TYPE type)
	{
		return StateMap[type];
	}

private:
	std::vector<XBKeyState*> states;

	float  TotalDuration;

	//key is action type, while value is state index 
	std::map<ACTION_TYPE, std::vector<int>> StateMap;
};

#endif // _ANIMATION_H