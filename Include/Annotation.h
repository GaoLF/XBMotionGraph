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

	//before�Ѿ�˵���ˣ�ann�����֣�һ����ѵ���ı�ע�ļ���һ�������ɶ����������ļ�
	//bAimed�������ı�ʶ��
	//�������ڣ�trainann��һЩ�ؼ���Ϣ��������ʱ������Ҫ�����ļ�����Ϣ�����
	//�����ɵ�tryann�������Զ������Ϣ�������������ļ�������
	bool LoadJson(std::string filename, bool bAimed = false);

	bool ParseJson(std::string filename);

	//By default the annotation does not annotated with idle state
	bool AddIdleState();

	bool ConstuctStateMap();

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

	//std::vector<XBTransition*> Trans;
};

#endif // _ANIMATION_H