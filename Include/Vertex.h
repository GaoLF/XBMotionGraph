#ifndef _VERTEX_H
#define _VERTEX_H

#include <string>
#include <vector>

#include "Pose.h"
#include "TypeDefinition.h"

using namespace std;

class XBVertex
{
	//Primary Function
	XBVertex()
	{

	};

	~XBVertex()
	{

	};

	//Public Function

	//Local Function

	//Public Variable

	//Local Variable
private:

	int Index;

	string Name;

	int FrameNum;

	vector<XBPose> Clips;


};

#endif//_VERTEX_H