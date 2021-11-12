#ifndef _GRAPH_H
#define  _GRAPH_H

#include "Edge.h"
#include "Node.h"
#include "Animation.h"
#include "Annotation.h"

class XBGraph
{
public:
	XBGraph()
	{

	};

	~XBGraph()
	{

	};

public:
	//Public Function
	bool Construction(XBAnimation* ani, XBAnnotation* ann);

	XBAnimation* Traverse(XBAnnotation* ann);

	void PrintMotionGraph();
	//Local Function

	//Public Variable

	//Local Variable

private:

	XBNode* Head;

	vector<XBNode*> Nodes;
	vector<XBEdge*> Edges;


};

#endif // _GRAPH_H