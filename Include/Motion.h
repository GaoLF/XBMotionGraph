#ifndef _MOTION_H
#define _MOTION_H

#include "TypeDefinition.h"
#include <vector>

class XBNode;

//if idle,no start end and peak
//Motion与Annotation的State是一一对应的
class XBMotion
{
	//Primary Function
public :
	XBMotion()
	{
		type = ACTION_TYPE::IDLE;
		annindex = 0;
	}

	~XBMotion()
	{

	};
	
	//Public Function
	int GetAnnIndex()
	{
		return annindex;
	}

	void SetAnnIndex(int value)
	{
		annindex = value;
	}
	
	void SetType(ACTION_TYPE value)
	{
		type = value;
	}

	ACTION_TYPE GetType()
	{
		return type;
	}



	//Local Function

	//Public Variable
public:



	//Local Variable

public:
	std::vector<XBNode*> start;
	std::vector<XBNode*> peak;
	std::vector<XBNode*> end;
private:
	ACTION_TYPE type;

	//map to the annotation state index
	int annindex;
};

class XBMotionEdge
{
	//Primary Function
public:
	XBMotionEdge()
	{
		type = MOTION_EDGE_TYPE::_2None;
	}

	~XBMotionEdge()
	{

	};

	std::vector<int>& GetPathArr()
	{
		return path;
	}

	void SetPathArr(std::vector<int> arr)
	{
		path = arr;
	}

	void SetStartMotionIndex(int value)
	{
		StartMotionIndex = value;
	}

	int GetStartMotionIndex()
	{
		return StartMotionIndex;
	}

	void SetEndMotionIndex(int value)
	{
		EndMotionIndex = value;
	}

	int GetEndMotionIndex()
	{
		return EndMotionIndex;
	}

	int GetEndNodeIndex()
	{
		return endNodeIndex;
	}

	void SetEndNodeIndex(int value)
	{
		endNodeIndex = value;
	}

	void SetType(MOTION_EDGE_TYPE value)
	{
		type = value;
	}

	MOTION_EDGE_TYPE GetType()
	{
		return type;
	}

private:

	std::vector<int> path;
	int StartMotionIndex;
	//是motion的index，而不是某一帧的index
	int EndMotionIndex;
	//是具体一帧的index
	int endNodeIndex;


	MOTION_EDGE_TYPE type;

};


#endif//_Motion_H