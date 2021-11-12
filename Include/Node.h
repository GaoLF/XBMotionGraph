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

using namespace std;

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

	//Local Function

	//Public Variable

	//Local Variable
private:

	int Index;
	XBPose* Pose;
	vector<XBEdge*> Edges;

	float Threshold;
};

#endif//_POSE_H