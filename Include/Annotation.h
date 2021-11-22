#ifndef _ANNOTATION_H
#define _ANNOTATION_H

//Make the Annotation Decoupled with the frame info.
//��ע��Ϣ��ֻ��ʱ���ǣ���֡��Ϣ����
//Animation����ʱ���֡������

//���ݶ�������ͼ��ʱ��Annotation����ʱ���Ǹ���Animation������
//���Ǹ���ͼ���ɶ�����ʱ��Annotation��ʱ��������Animation��ʱ��

#include <string>
#include <vector>
#include <map>
#include "TypeDefinition.h"
#include "Transition.h"

class XBGraph;

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

	vector<XBTransition*>& GetTrans()
	{
		return Trans;
	}

	int GetTransNum()
	{
		return (int)Trans.size();
	}

	bool LoadJson(std::string filename);

	bool ParseJson(std::string filename);

	//By default the annotation does not annotated with idle state
	bool AddIdleState();

	bool ConstuctStateMap();

	bool ConstuctTrans();

	bool SortStates();

	std::vector<int>& FindArrayofType(ACTION_TYPE type)
	{
		return StateMap[type];
	}

private:
	std::vector<XBKeyState*> states;

	float  TotalDuration;

	//key is action type, while value is state index 
	std::map<ACTION_TYPE, std::vector<int>> StateMap;

	std::vector<XBTransition*> Trans;
};

#endif // _ANIMATION_H