#ifndef _GRAPH_H
#define  _GRAPH_H

#include "Edge.h"
#include "Node.h"
#include "Animation.h"
#include "Annotation.h"

//图的构造和生成需要一个ann和ani
//用图生成一个新的动画，需要另一个ann

//我把每一个部分叫做Section
//Section有两种，Key Section和Transition Section

//后续的选取section算法中会考虑到section的长度和实际state的长度关联

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
	
	
	//Local Function
	int RandomSelectKeySectionIndexInGraph(ACTION_TYPE type);

	//两种设置关键Section的方法
	//选取第一个符合要求的Section，也是我在做demo中需要的
	//另一个是随机的选取
	bool TraverseHandleKeySection(XBAnimation* RetAni, XBAnnotation* ann);

	//L = tran C = tran
	//L = tran C = KeyA
	//L = KeyA C = KeyA
	//L = KeyA C = tran
	//L = KeyA C = KeyB
	bool TraverseHandleRestSection(XBAnimation* ani, XBAnnotation* ann);
	

	//Public Variable

	//Local Variable

private:

	vector<XBNode*> Nodes;
	vector<XBEdge*> Edges;

	XBAnimation* Animation;
	XBAnnotation* Annotation;
};

#endif // _GRAPH_H