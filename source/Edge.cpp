#include "Edge.h"
#include "Node.h"

XBEdge::XBEdge()
{
	Src = new XBNode();
	Dst = new XBNode();
}

XBEdge::~XBEdge()
{
	delete Src;
	delete Dst;
}