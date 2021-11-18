#include "Graph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

#include "Cost.h"
#include "TypeDefinition.h"
using namespace std;

XBGraph::XBGraph()
{
	Head = new XBNode();
};

XBGraph::~XBGraph()
{
	delete Head;
	for (int i = 0; i < (int)Nodes.size(); i++)
	{
		delete Nodes[i];
	}
	for (int i = 0; i < (int)Edges.size(); i++)
	{
		delete Edges[i];
	}
};

bool XBGraph::Construction(XBAnimation* ani, XBAnnotation* ann)
{
	
	if (ani == NULL)
		return false; 

	vector<XBPose*> poses = ani->GetAni();
	int NodeNum = poses.size();

	//This part is wrote badly
	//Inverse trans the vector, to assign the Edge "i -> i + 1"
	for (int i = NodeNum - 1; i >= 0; i--)
	{
		XBNode* newNode = new XBNode();
		newNode->SetPose(poses[i]);

		//Set the Threshold
		float threshold = DEFAULT_NODE_THRESHOLD;
		if ((i + 3) < (int)poses.size())
		{
			threshold = XBCost::Dist(poses[i], poses[i + 3]);
		}
		else if (i > 3)
		{
			threshold = XBCost::Dist(poses[i], poses[i - 3]);
		}

		if ((i + 1) < (int)poses.size() && Nodes.size() > 0)
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

		cout << "               \r";
		cout << (float)i / (float)NodeNum * 100.f << "%\r";
		
	}
	cout << endl;

	cout << "Succeed to Construct the Motion Graph!" << endl;
	return true;
}


XBAnimation* XBGraph::Traverse(XBAnnotation* ann, int firstframeindex)
{
	if (ann == NULL)
		return NULL;

	XBAnimation* NewAni = new XBAnimation();

	if (TraverseHandleFirstFrame(NewAni, ann, firstframeindex) == NULL)
	{
		cerr << "Failed to Construct the First Pose of the Animation by Traversing the graph!" << endl;
		return NULL;
	}

	int startframe = 1;

	if (TraverseHandleRestFrame(NewAni, ann, startframe) == false)
	{
		cerr << "Failed to Construct the rest frames of the Animation by Traversing the graph!" << endl;
		return NULL;
	}


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

bool XBGraph::SaveMotionGraphData(string file)
{
	ofstream outFile(file);

	if (!outFile)
	{
		cout << "Init the output file error" << endl;
		return false;
	}

	string DataStr;

	DataStr += to_string(Nodes.size()) + "\n";

	for (int i = 0; i < (int)Nodes.size(); i++)
	{
		DataStr = to_string(Nodes[i]->GetIndex()) + " ";

		for (int j = 0; j < (int)Nodes[i]->GetEdges().size(); j++)
		{
			DataStr += Nodes[i]->GetEdges()[j]->GetDst()->GetIndex() + " ";
			DataStr += to_string(Nodes[i]->GetEdges()[j]->GetDist()) + " ";
		}
		DataStr += "\n";
	}

	for (int i = 0; i < (int)Nodes.size(); i++)
	{
		if (Nodes[i]->GetPose() == NULL)
			continue;

		DataStr += to_string(Nodes[i]->GetIndex()) + " ";

		DataStr += to_string((int)Nodes[i]->GetPose()->GetFlag()) + " ";

		for (int j = 0; j < (int)Nodes[i]->GetPose()->GetLocations().size(); j++)
		{
			if (j >= (int)Nodes[i]->GetPose()->GetRotations().size())
				continue;
			Eigen::Vector3f tmp_loc = Nodes[i]->GetPose()->GetLocations()[j];
			Eigen::Vector3f tmp_rot = Nodes[i]->GetPose()->GetRotations()[j];
			DataStr += to_string(tmp_loc[0]) + " " + to_string(tmp_loc[1]) + " " + to_string(tmp_loc[2]) + " ";
			DataStr += to_string(tmp_rot[0]) + " " + to_string(tmp_rot[1]) + " " + to_string(tmp_rot[2]) + " ";
		}

	}

	outFile << DataStr;
	outFile.close();


	cout << "Succeed to Save the Graph to data" << endl;

	return true;
}

bool XBGraph::LoadMotionGraphData(string file)
{
	ifstream inFile(file, ios::in);

	if (!inFile)
	{
		cout << "Can't find this file" << endl;
		return false;
	}

	char c[10000];

	int flag = 0;
	int NodeNum = -1;
	int NodeIndex = 0;
	//three parts
	//0, nodes num
	//1, edges
	//2, nodes ani
	while (inFile.getline(c, 10000))
	{
		string tmp = c;
		if (flag == 0)
		{
			NodeNum = atoi(tmp.c_str());
			flag = 1;

			for (int i = 0; i < NodeNum; i++)
			{
				XBNode* newNode = new XBNode();
				newNode->SetIndex(i);
				Nodes.push_back(newNode);
			}
		}
		else if (flag == 1)
		{
			if (NodeIndex == NodeNum)
			{
				flag = 2;
				NodeIndex = 0;
				continue;
			}

			vector<string> splitstrs;
			split(tmp, splitstrs, " ");
			
			if (splitstrs.size() < 2)
			{
				cerr << "Load Motion Graph Data Error - Edges load error" << endl;
				return false;
			}

			//the first item is the node index
			int tmp_node_index = (int)atoi(splitstrs[0].c_str());
			if (tmp_node_index != NodeIndex)
				continue;

			XBNode* tmpNode = Nodes[NodeIndex];
			
			int length = (int)splitstrs.size();
			int edgeNum = (length - 1) / 2;
			for (int j = 1; j < edgeNum; j += 2)
			{
				int tmp_index  = (int)atoi(splitstrs[j].c_str());
				float tmp_dist = (float)atof(splitstrs[j + 1].c_str());

				XBEdge* newEdge = new XBEdge();
				newEdge->SetSrc(tmpNode);
				if (tmp_index < NodeNum)
				{
					newEdge->SetDst(Nodes[tmp_index]);
				}
				newEdge->SetDist(tmp_dist);
		
				tmpNode->AddEdge(newEdge);
			}

			NodeIndex++;
		}
		else if (flag == 2)
		{
			if (NodeIndex >= NodeNum)
				break;

			vector<string> splitstrs;
			split(tmp, splitstrs, " ");

			if (splitstrs.size() < 3)
			{
				cerr << "Load Motion Graph Data Error - Animation load error" << endl;
					return false;
			}

			//the first item is the node index
			int tmp_node_index = (int)atoi(splitstrs[0].c_str());
			if (tmp_node_index != NodeIndex)
				continue;

			int tmp_flag = (int)atoi(splitstrs[1].c_str());

			XBNode* tmpNode = Nodes[NodeIndex];
			XBPose* newPose = new XBPose();
			newPose->SetFlag((ACTION_TYPE)tmp_flag);

			int length = (int)splitstrs.size();
			//3: Eigen::Vector3f.xyz
			//2: location and rotation
			int skeletonnum = (length - 1) / (3 * 2);
			Eigen::Vector3f tmp_loc, tmp_rot;
			for (int j = 0; j < skeletonnum; j++)
			{
				bool condition = (3 * j + 2 + 2 + 3 * skeletonnum) < length && (3 * j + 2 + 2) < length;
				if (!condition)
					continue;

				tmp_loc[0] = (float)atof(splitstrs[3 * j + 0 + 2].c_str());
				tmp_loc[1] = (float)atof(splitstrs[3 * j + 1 + 2].c_str());
				tmp_loc[2] = (float)atof(splitstrs[3 * j + 2 + 2].c_str());

				tmp_rot[0] = (float)atof(splitstrs[3 * j + 0 + 2 + 3 * skeletonnum].c_str());
				tmp_rot[1] = (float)atof(splitstrs[3 * j + 1 + 2 + 3 * skeletonnum].c_str());
				tmp_rot[2] = (float)atof(splitstrs[3 * j + 2 + 2 + 3 * skeletonnum].c_str());

				newPose->AddLocation(tmp_loc);
				newPose->AddRotation(tmp_rot);
				
				tmpNode->SetPose(newPose);
			}
			
			NodeIndex++;
		}
	}

	inFile.close();
	cout << "Succeed to Load the Graph from data" << endl;
	return true;
		
}

int XBGraph::RandomSelectFirstFrame(ACTION_TYPE type, XBAnnotation* ann)
{
	vector<int> tmp_arr = ann->FindArrayofType(type);

	int rand_index = GetRandomNum(0, (int)tmp_arr.size());

	//Nodes->push_back();

	return 0;
}

bool XBGraph::TraverseHandleFirstFrame(XBAnimation* ani, XBAnnotation* ann, int firstframeindex)
{
	XBKeyState* firstState = ann->GetState(0);
	ACTION_TYPE first_type = ACTION_TYPE::IDLE;
	int actual_firstframeindex = 0;

	if (firstState)
	{
		if (firstState->start < 0.00001f && firstState->start > 0.00001)
		{
			first_type = firstState->action;
		}
	}

#if FIRST_FRAME_RANDOMACESS

	actual_firstframeindex = RandomSelectFirstFrame(first_type, Nodes.size());

#elif FIRST_FRAME_ASSIGNED

	actual_firstframeindex = firstframeindex;

	//XBPose* firstnode;
	if (firstframeindex < 0 || firstframeindex > (int)Nodes.size())
	{
		actual_firstframeindex = RandomSelectFirstFrame(first_type, ann);
	}
	if (firstframeindex < (int)Nodes.size() && Nodes[firstframeindex]->GetPose())
	{
		if (Nodes[firstframeindex]->GetPose()->GetFlag() != first_type)
		{
			actual_firstframeindex = RandomSelectFirstFrame(first_type, ann);
		}
	}

#endif

	if (actual_firstframeindex < (int)Nodes.size() && Nodes[actual_firstframeindex]->GetPose())
	{
		ani->AddPose(Nodes[actual_firstframeindex]->GetPose());
		return true;
	}
	else
	{
		return false;
	}
}

bool XBGraph::TraverseHandleRestFrame(XBAnimation* ani, XBAnnotation* ann)
{
	if (ani == NULL || ann == NULL || curframe < 1 || curframe >= (int)Nodes.size())
		return false;

	if (Nodes.size() < 1)
		return false;
	
	ACTION_TYPE tmp_type = Nodes[0]->GetPose()->GetFlag();

	while (curframe > 1 || curframe < (int)Nodes.size())
	{
		
	}

	XBNode* tmp_node = Nodes[curframe];
	
	return true;
}