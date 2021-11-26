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


	//一个Node的array是一个path
	//过渡边的目的就是找到代价最低的一个Path
	vector<vector<XBNode*>> Paths;

	//index和Path是一一对应的
	vector<float> Costs;

};

#endif//_VTRANSITION_H