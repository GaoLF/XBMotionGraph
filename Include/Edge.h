#ifndef _EDGE_H
#define _EDGE_H

#include "Pose.h"

class XBEdge
{
public:
	XBEdge();


private:

	XBPose* Src;
	XBPose* Dst;
};
#endif // _EDGE_H