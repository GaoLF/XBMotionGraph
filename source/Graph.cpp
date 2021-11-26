#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

#include "Graph.h"
#include "Cost.h"
#include "TypeDefinition.h"
#include "Motion.h"
using namespace std;

XBGraph::XBGraph()
{
	
};

XBGraph::~XBGraph()
{
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

	Animation = ani;
	Annotation = ann;

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

#if TEST_METHOD_2
	ConstructMotions();
#endif

	cout << "Succeed to Construct the Motion Graph!" << endl;
	return true;
}


XBAnimation* XBGraph::Traverse(XBAnnotation* tryann)
{
	if (tryann == NULL)
		return NULL;

	XBAnimation* NewAni = new XBAnimation();

	if (TraverseHandleKeySection(NewAni, tryann) == false)
	{
		cerr << "Failed to Construct the Key Section of the Animation by Traversing the graph!" << endl;
		return NULL;
	}

	if (TraverseHandleRestSection(NewAni, tryann) == false)
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

		DataStr += to_string((int)Nodes[i]->GetType()) + " ";

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
			tmpNode->SetType((ACTION_TYPE)tmp_flag);

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

int XBGraph::RandomSelectKeySectionIndexInGraph(ACTION_TYPE type)
{
	int num = Annotation->FindArrayofType(type).size();

	int index = GetRandomNum(num);

	return index;
}

XBKeyState* XBGraph::RandomSelectKeyStateInGraph(ACTION_TYPE type)
{
	return Annotation->GetState(RandomSelectKeySectionIndexInGraph(type));
}

bool XBGraph::TraverseHandleKeySection(XBAnimation* RetAni, XBAnnotation* tryann)
{
	if (RetAni == NULL)
	{
		return false;
	}

	float total_Duration = tryann->GetTotalDuration();
	int total_Frame = (int)(total_Duration * FPS);
	if ((int)RetAni->GetAni().size() < total_Frame)
	{
		for (int i = (int)RetAni->GetAni().size(); i < total_Frame; i++)
		{
			XBPose* newPose = new XBPose();
			RetAni->AddPose(newPose);
		}
	}

	for (int i = 0; i < (int)tryann->GetStates().size(); i++)
	{
		XBKeyState* try_state = tryann->GetState(i);
		if (try_state != NULL)
		{
			ACTION_TYPE type = tryann->GetState(i)->action;
#if SECTION_RANDOMACESS

			XBKeyState* state = RandomSelectKeyStateInGraph(type);
			
			if (state == nullptr)
				continue;

			float start = state->start;
			float end = state->end;
			int start_frame = int(start * FPS);
			int end_frame = int(end * FPS);
			int max_section_size = (int)((try_state->end - try_state->start) * FPS);
			int begin_frame = (int)(try_state->start * FPS);

			for (int j = start_frame; j < end_frame; j++)
			{
				if (j < (int)Animation->GetAni().size())
				{
					int cur_section_size = j - start_frame;
					
					if (cur_section_size < max_section_size)
					{
						Animation->GetAni()[begin_frame + cur_section_size] = Nodes[j]->GetPose();
					}
				}
			}

#elif SECTION_ASSIGNED

#endif
		}
	}

	return true;
	
}

bool XBGraph::TraverseHandleRestSection(XBAnimation* RetAni, XBAnnotation* tryann)
{
	int count = GetTransNum();
	for (int i = 0; i < count; i++)
	{
		XBTransition* tmp_Tran = GetTrans()[i];

		if (HandleTran(tmp_Tran) == false)
		{
			cerr << "Failed to Traverse Tran:" << i << endl;
			return false;
		}
	}

	return true;
}

bool XBGraph::HandleTran(XBTransition* tran)
{
	if (tran == nullptr)
		return false;
	if (Animation == NULL)
		return false;

	int TotalFrame = Animation->GetFrameNum();
	if (TotalFrame != Animation->GetAni().size())
		return false;

	float start = tran->GetStart();
	float end = tran->GetEnd();
	int start_frame = (int)(start * FPS) + 1;
	int end_frame = (int)(end * FPS) - 1;

	int start_refer_frame = start_frame - 1;
	int end_refer_frame = end_frame + 1;

	if (start_refer_frame < 0 || start_frame < 0 || end_frame > TotalFrame || end_refer_frame > TotalFrame)
	{
		return false;
	}

	if (Animation->GetPose(start_refer_frame)->GetIndex() >= (int)Nodes.size() ||
		Animation->GetPose(end_refer_frame)->GetIndex() >= (int)Nodes.size())
		return false;

	XBNode* start_refer_Node = Nodes[Animation->GetPose(start_refer_frame)->GetIndex()];
	XBNode* end_refer_Node = Nodes[Animation->GetPose(end_refer_frame)->GetIndex()];;

	if (start_refer_Node || !end_refer_Node)
		return false;

	int num_frame = end_frame - start_frame + 1;
	XBNode* tmp_Node = start_refer_Node;

#if TEST_METHOD_1
	vector<vector<int>> paths;


	for (int i = 0; i < num_frame; i++)
	{
		for (int NodeIndex = 0; NodeIndex < SAVED; NodeIndex++)
		{
			if(NodeIndex < (int)tmp_Node->GetEdges().size())
			{
				XBNode* next_Node = tmp_Node->GetEdge(NodeIndex)->GetDst();
				if (next_Node)
				{

				}
			}
		}
	}
#endif

	return true;
}


bool XBGraph::ConstructTrans(XBAnnotation* tryann)
{
	int length = (int)tryann->GetStates().size();

	for (int i = 0; i < length; i++)
	{
		if ((i + 1) < length)
		{
			if (tryann->GetState(i)->end < tryann->GetState(i + 1)->start)
			{
				XBTransition* newTrans = new XBTransition();
				newTrans->SetStart(tryann->GetState(i)->end);
				newTrans->SetEnd(tryann->GetState(i + 1)->start);

				Trans.push_back(newTrans);
			}
		}
	}

	return true;
}

#if TEST_METHOD_2

bool XBGraph::SetMotionState()
{
	if (!Annotation || !Animation)
		return false;

	int length = Annotation->GetStates().size();
	for (int stateindex = 0; stateindex < length; stateindex++)
	{
		XBKeyState* state = Annotation->GetState(stateindex);

		XBMotion* newmotion = new XBMotion();
		newmotion->SetAnnIndex(stateindex);
		newmotion->SetType(state->action);
		int startframe = int(state->start * float(FPS));
		int endframe = int(state->end * float(FPS));

		if (state->action == ACTION_TYPE::IDLE)
		{
			for (int i = startframe; i < endframe; i++)
			{
				if (i < Nodes.size())
				{
					newmotion->peak.push_back(Nodes[i]);
					Nodes[i]->SetState(ACTION_STATE::None);
					Nodes[i]->SetMotionIndex(stateindex);
				}
			}
		}
		else
		{
			int i = 0;
			for (; i < ACTION_START_FRAME_NUM; i++)
			{
				if (startframe + i < (int)Nodes.size())
				{
					newmotion->start.push_back(Nodes[startframe + i]);
					Nodes[startframe + i]->SetState(ACTION_STATE::START);
					Nodes[startframe + i]->SetMotionIndex(stateindex);
				}
			}

			int j = 0;
			for (; j < ACTION_END_FRAME_NUM; j++)
			{
				if (endframe - j < (int)Nodes.size())
				{
					newmotion->end.push_back(Nodes[endframe - j]);
					Nodes[endframe - j]->SetState(ACTION_STATE::END);
					Nodes[endframe - j]->SetMotionIndex(stateindex);
				}
			}

			for (int m = i + startframe; m < endframe - j; m++)
			{
				if (m < (int)Nodes.size())
				{
					newmotion->peak.push_back(Nodes[m]);
					Nodes[m]->SetState(ACTION_STATE::PEAK);
					Nodes[m]->SetMotionIndex(stateindex);
				}
			}
		}

		motions.push_back(newmotion);
	}
}

bool XBGraph::ConstructMotions()
{
	if (SetMotionState() == false)
		return false;

	int length = (int)Nodes.size();

	//遍历所有node
	for (int nodeindex = 0; nodeindex < length; nodeindex++)
	{
		//选取End State Node作为root
		XBNode* root_node = Nodes[nodeindex];
		if (root_node->GetState() == ACTION_STATE::END)
		{
			vector<XBNode*> Tmp_node_Array, Tmp_node_Array2;
			Tmp_node_Array.push_back(root_node);

			//构造当前End Node的十层Path
			for (int level = 0; level < MOTION_EDGE_FRAMENUM; level++)
			{
				vector<XBMotionEdge*> cur_level_edge_arr;
				Tmp_node_Array2.clear();

				//遍历Tmp_node_Array，构建当前Tmp_node_Array2
				for (int cur_level_startnode_index = 0; cur_level_startnode_index < (int)Tmp_node_Array.size(); cur_level_startnode_index++)
				{
					XBNode* cur_level_startnode = Tmp_node_Array[cur_level_startnode_index];
					if (cur_level_startnode)
					{
						vector<int> cur_level_path = root_node->CurrentLevelPath(level - 1, cur_level_startnode);
						for (int edge_index = 0; edge_index < (int)cur_level_startnode->GetEdges().size(); edge_index++)
						{
							XBNode* cur_level_dstnode = cur_level_startnode->GetEdge(edge_index)->GetDst();

							if (root_node->EdgesContainNode(level - 1, cur_level_dstnode) == false)
							{
								if (find(Tmp_node_Array2.begin(), Tmp_node_Array2.end(), cur_level_dstnode) != Tmp_node_Array2.end())
								{
									Tmp_node_Array2.push_back(cur_level_dstnode);
									vector<int> path = cur_level_path;
									path.push_back(cur_level_dstnode->GetIndex());

									XBMotionEdge* newMotionEdge = new XBMotionEdge();
									newMotionEdge->SetPathArr(path);
									newMotionEdge->SetStartMotionIndex(root_node->GetMotionIndex());
									newMotionEdge->SetEndMotionIndex(cur_level_dstnode->GetMotionIndex());
									newMotionEdge->SetEndNodeIndex(cur_level_dstnode->GetIndex());

									if (cur_level_dstnode->GetType() == ACTION_TYPE::IDLE)
									{
										newMotionEdge->SetType(MOTION_EDGE_TYPE::_2IDLE);
									}
									else if (cur_level_dstnode->GetType() != ACTION_TYPE::IDLE && cur_level_dstnode->GetType() != ACTION_TYPE::NONE
										&& cur_level_dstnode->GetState() == ACTION_STATE::START)
									{
										newMotionEdge->SetType(MOTION_EDGE_TYPE::_2MOTIONSTART);
									}
									else
									{
										newMotionEdge->SetType(MOTION_EDGE_TYPE::_2None);
									}

									//存的edges里包含了很多的2node，这些边实际遍历中是没有用的，增加很多搜索成本
									//但是构建下一步的path时不能没有
									//所以我认为，应该在构建之后，把所有的2none都给删了
									cur_level_edge_arr.push_back(newMotionEdge);
								}
								else
								{
									continue;
								}
								

							}
						}
					}
				}
				
				int cur_rootnode_MotionEdges_length = (int)root_node->GetMotionEdges().size();
				if (cur_rootnode_MotionEdges_length <= level)
				{
					for (int foo = cur_rootnode_MotionEdges_length; foo < (level + 1); foo ++)
					{
						root_node->GetMotionEdges().push_back(vector<XBMotionEdge*>());
					}
				}

				root_node->GetMotionEdges()[level] = cur_level_edge_arr;
				Tmp_node_Array = Tmp_node_Array2;
			}
		}
	}

	return true;
}

#endif 
