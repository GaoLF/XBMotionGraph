#ifndef _GRAPH_H
#define  _GRAPH_H

#include "Edge.h"
#include "Node.h"
#include "Animation.h"
#include "Annotation.h"

class XBMotion;

//图的构造和生成需要一个ann(trainann)和ani
//用图生成一个新的动画，需要另一个ann(tryann)

class XBGraph
{
public:

	XBGraph();

	~XBGraph();

public:
	//Public Function
	bool Construction(XBAnimation* ani, XBAnnotation* ann);

	XBAnimation* Traverse(XBAnnotation* tryann);

	//Print the Nodes and Edges
	void PrintMotionGraph();

	//Motion Graph Data Format:
	//--------Nodes Number
	//--------//Dst: the edge is Node1->Dst1 and Dist is the distance between them
	//--------Node1 Dst1 Dist1 Dst2 Dist2..
	//--------Node2 Dst1 Dist1 Dst2 Dist3..
	//--------//Nodes Animation Data
	//--------Node1.Index Node1.flag Location Rotation
	bool LoadMotionGraphData(string file);

	//Motion Graph Data Format:
	//--------Nodes Number
	//--------//Dst: the edge is Node1->Dst1 and Dist is the distance between them
	//--------Node1 Dst1 Dist1 Dst2 Dist2..
	//--------Node2 Dst1 Dist1 Dst2 Dist3..
	//--------//Nodes Animation Data
	//--------Node1.Index Node1.flag Location Rotation
	bool SaveMotionGraphData(string file);
	
	vector<XBTransition*>& GetTrans()
	{
		return Trans;
	}

	int GetTransNum()
	{
		return (int)Trans.size();
	}

	
	//Local Function
	int RandomSelectKeySectionIndexInGraph(ACTION_TYPE type);

	XBKeyState* RandomSelectKeyStateInGraph(ACTION_TYPE type);

	//两种设置关键Section的方法
	//选取第一个符合要求的Section，也是我在做demo中需要的
	//另一个是随机的选取
	bool TraverseHandleKeySection(XBAnimation* RetAni, XBAnnotation* ann);

	//Handle the all the Trans
	bool TraverseHandleRestSection(XBAnimation* ani, XBAnnotation* ann);
	
	//Handle One Tran 
	//我曾想把start node和end node存到tran里，但是annotation需要反向耦合graph，有问题
	//还是把trans存到graph
	bool HandleTran(XBTransition* tran);

	bool ConstructTrans(XBAnnotation* tryann);

#if TEST_METHOD_2
	bool ConstructMotions();

#endif

	bool SetMotionState();


	//Public Variable

	//Local Variable

private:

	vector<XBNode*> Nodes;
	vector<XBEdge*> Edges;

	XBAnimation* Animation;
	XBAnnotation* Annotation;

	//为了输出而设置的
	vector<XBTransition*> Trans;

#if TEST_METHOD_2
	vector<XBMotion*> motions;
#endif
};

#endif // _GRAPH_H