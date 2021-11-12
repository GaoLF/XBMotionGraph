#include "Graph.h"
#include <iostream>
#include "Cost.h"
using namespace std;

bool XBGraph::Construction(XBAnimation* ani, XBAnnotation* ann)
{
	
	if (ani == NULL)
		return false; 

	vector<XBPose*> poses;
	int NodeNum = poses.size();

	//This part is wrote badly
	//Inverse trans the vector, to assign the Edge "i -> i + 1"
	for (int i = NodeNum - 1; i >= 0; i--)
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
			newEdge->SetSrc(newNode);
			newEdge->SetDst(newNode);

			newNode->AddEdge(newEdge);
		}

		Nodes.push_back(newNode);
	}

	for (int i = 0; i < NodeNum; i++)
	{
		XBNode* CurNode = Nodes[i];
		for (int j = 0; j < NodeNum; j++)
		{
			if (j == (i + 1) || j == i)
				continue;

			float threshold = CurNode->GetThreshold();

			float dist = XBCost::Dist(CurNode->GetPose(), Nodes[j]->GetPose());
			if (dist < threshold)
			{
				XBEdge* newEdge = new XBEdge;
				newEdge->SetSrc(CurNode);
				newEdge->SetDst(Nodes[j]);
				CurNode->AddEdge(newEdge);
			}
		}
	}

	cout << "Succeed to Construct the Motion Graph!" << endl;
	return true;
}


XBAnimation* XBGraph::Traverse(XBAnnotation* ann)
{
	XBAnimation* NewAni = new XBAnimation();

	return NewAni;
}


void XBGraph::PrintMotionGraph()
{
	int nodenum = Nodes.size();

	for (int i = 0; i < nodenum; i++)
	{
		cout << "Node " << i << ": ";
		for (size_t j = 0; j < Nodes[i]->GetEdges().size(); j++)
		{
			cout << to_string(Nodes[i]->GetEdge(j)->GetDst()->GetIndex()) << ", ";
		}
	}
}

