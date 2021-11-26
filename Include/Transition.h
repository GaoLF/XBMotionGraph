#ifndef _VTRANSITION_H
#define _VTRANSITION_H

#include "Node.h"
using namespace std;

class XBTransition
{
public:
	//Primary Function
	XBTransition();


	~XBTransition()
	{

	};

	//Public Function
	void SetStart(float value)
	{
		start = value;
	}

	void SetEnd(float value)
	{
		end = value;
	}

	float GetStart()
	{
		return start;
	}

	float GetEnd()
	{
		return end;
	}

	//Local Function

	//Public Variable

	//Local Variable

private:

	//the start time of the result Ani section
	float start;

	//the end time of the result Ani section
	float end;


	//һ��Node��array��һ��path
	//���ɱߵ�Ŀ�ľ����ҵ�������͵�һ��Path
	vector<vector<XBNode*>> Paths;

	//index��Path��һһ��Ӧ��
	vector<float> Costs;

};

#endif//_VTRANSITION_H