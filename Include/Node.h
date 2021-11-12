#ifndef _NODE_H
#define _NODE_H

//One Node is Indeed One Frame
//Somehow One Vertex is One Clip
#include <vector>

#include "Pose.h"
#include "Edge.h"
#include "Animation.h"
#include "TypeDefinition.h"

using namespace std;

class XBNode
{
	//Primary Function
public :
	XBNode()
	{
		Pose = new XBPose();
		Threshold = DEFAULT_NODE_THRESHOLD;
	};

	~XBNode()
	{

	};

	//Public Function

	void SetPose(XBPose* pose)
	{
		Pose = pose;
	}

	void AddEdge(XBEdge* edge)
	{
		Edges.push_back(edge);
	}

	float GetThreshold()
	{
		return Threshold;
	}

	void SetThreshold(float value)
	{
		Threshold = value;
	}

	//Local Function

	//Public Variable

	//Local Variable
private:

	XBPose* Pose;
	vector<XBEdge*> Edges;

	float Threshold;
};

#endif//_POSE_H