#ifndef _NODE_H
#define _NODE_H

//One Node is Indeed One Frame
//Somehow One Vertex is One Clip

#include "Pose.h"
#include "Edge.h"
#include "Animation.h"
#include "TypeDefinition.h"
#include <iostream>
#include <vector>

class XBMotionEdge;

class XBNode
{
	//Primary Function
public :
	XBNode()
	{
		Pose = new XBPose();
		Threshold = DEFAULT_NODE_THRESHOLD;
		Index = 0;
	};

	~XBNode()
	{

	};

	//Public Function

	XBPose* GetPose()
	{
		return Pose;
	}

	void SetPose(XBPose* pose)
	{
		Pose = pose;
	};

	void AddEdge(XBEdge* edge)
	{
		if (std::find(Edges.begin(), Edges.end(), edge) != Edges.end())
			Edges.push_back(edge);
	};

	vector<XBEdge*>& GetEdges()
	{
		return Edges;
	}

	XBEdge* GetEdge(int index)
	{
		return Edges[index];
	}

	float GetThreshold()
	{
		return Threshold;
	};

	void SetThreshold(float value)
	{
		Threshold = value;
	};

	void SetIndex(int value)
	{
		Index = value;
	}

	int GetIndex()
	{
		return Index;
	}

	ACTION_TYPE GetType()
	{
		return type;
	}

	void SetType(ACTION_TYPE value)
	{
		type = value;
	}

#if TEST_METHOD_2
	ACTION_STATE GetState()
	{
		return state;
	}

	void SetState(ACTION_STATE value)
	{
		state = value;
	}

	void SetMotionIndex(int value)
	{
		MotionIndex = value;
	}

	int GetMotionIndex()
	{
		return MotionIndex;
	}

	//当前节点的edges种，前pastlevel中包含node节点与否
	bool EdgesContainNode(int prelevel, XBNode* node);

	//当前level以node为终点的path
	std::vector<int> CurrentLevelPath(int level, XBNode* node);

	std::vector<std::vector<XBMotionEdge*> >& GetMotionEdges()
	{
		return motionedges;
	}


#endif

	//Local Function

	//Public Variable

	//Local Variable
private:

	int Index;
	XBPose* Pose;
	std::vector<XBEdge*> Edges;

	float Threshold;

	ACTION_TYPE type;

#if TEST_METHOD_2
	ACTION_STATE state;
	std::vector<std::vector<XBMotionEdge*> > motionedges;

	int MotionIndex;
#endif

};

#endif//_POSE_H