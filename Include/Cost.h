#ifndef _COST_H
#define _COST_H

#include "Pose.h"

//Involve two Cost Calculation Method
//One is the Distance between two Nodes, the other is between two Vertexes.
class XBCost
{
	//Primary Function
public :
	XBCost();

	~XBCost()
	{

	};

	//Local Function

	//Public Variable
public:
	static float Dist(XBPose* pose1, XBPose* pose2);


	//Local Variable
};

#endif//_COST_H