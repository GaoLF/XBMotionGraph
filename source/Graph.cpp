#include "Graph.h"
#include <iostream>
#include "Cost.h"
using namespace std;

bool XBGraph::Construction(XBAnimation* ani, XBAnnotation* ann)
{
	
	if (ani == NULL)
		return false; 

	vector<XBPose*> poses;

	//Inverse trans the vector, to assign the Edge "i -> i + 1"
	for (size_t i = poses.size(); i >= 0; i--)
	{
		XBNode* newNode = new XBNode();
		newNode->SetPose(poses[i]);

		//Set the Threshold
		float threshold = DEFAULT_NODE_THRESHOLD;
		if (i + 3 < poses.size())
		{
			threshold = XBCost::Dist(poses[i], poses[i + 3]);
		}
		else if (i > 3)
		{
			threshold = XBCost::Dist(poses[i], poses[i - 3]);
		}

		if (i + 1 < poses.size() && Nodes.size() > 0)
		{
			XBEdge* newEdge = new XBEdge();
			XBNode* node = Nodes[Nodes.size() - 1];
			newEdge->Target
		}

		Nodes.push_back(newNode);
	}




	cout << "Succeed to Construct the Motion Graph!" << endl;
	return true;
}


XBAnimation* XBGraph::Traverse(XBAnnotation* ann)
{
	XBAnimation* NewAni = new XBAnimation();

	return NewAni;
}
