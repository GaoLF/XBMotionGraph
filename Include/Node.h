#ifndef _NODE_H
#define _NODE_H

#include <vector>

#include "Pose.h"
#include "Edge.h"
#include "Animation.h"
#include "TypeDefinition.h"

using namespace std;

class XBNode
{
	//Primary Function
	XBNode()
	{

	};

	~XBNode()
	{

	};

	//Public Function

	//Local Function

	//Public Variable

	//Local Variable
private:

	XBPose* Pose;
	vector<XBEdge*> Edges;
};

#endif//_POSE_H