#ifndef _GRAPH_H
#define  _GRAPH_H

#include "Edge.h"
#include "Node.h"
#include "Animation.h"
#include "Annotation.h"

class XBGraph
{
public:

	XBGraph();

	~XBGraph();

public:
	//Public Function
	bool Construction(XBAnimation* ani, XBAnnotation* ann);

	XBAnimation* Traverse(XBAnnotation* ann, int firstframeindex = 0);

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
	int RandomSelectFirstFrame(ACTION_TYPE type, XBAnnotation* ann);
	
	bool TraverseHandleFirstFrame(XBAnimation* ani, XBAnnotation* ann, int firstframeindex = 0);

	//性能考虑，不用递归了
	//这个方法其实用递归会容易很多
	//默认从index=1帧开始
	bool TraverseHandleRestFrame(XBAnimation* ani, XBAnnotation* ann);
	

	//Public Variable

	//Local Variable

private:

	XBNode* Head;

	vector<XBNode*> Nodes;
	vector<XBEdge*> Edges;


};

#endif // _GRAPH_H