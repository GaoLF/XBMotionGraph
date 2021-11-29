#include "Node.h"
#include "TypeDefinition.h"
#include "Motion.h"

#if TEST_METHOD_2
bool XBNode::EdgesContainNode(int prelevel,XBNode* node)
{
	if (prelevel < 0)
		return false;

	for (int i = 0; i < prelevel; i++)
	{
		if (i >= (int)motionedges.size())
			continue;
		for (int j = 0; j < (int)motionedges[i].size(); i++)
		{
			XBMotionEdge* edge = motionedges[i][j];
			for (int m = 0; m < (int)edge->GetPathArr().size(); m++)
			{
				if (node->GetIndex() == edge->GetPathArr()[m])
					return true;
			}
		}
	}
	return false;
}

vector<int> XBNode::CurrentLevelPath(int level, XBNode* node)
{
	if (node && level >= 0 && level < (int)motionedges.size())
	{
		int length = (int)motionedges[level].size();
		for (int i = 0; i < length; i++)
		{
			XBMotionEdge* medge = motionedges[level][i];
			if (medge)
			{
				if ((int)medge->GetPathArr().size() > 0)
				{
					if (medge->GetPathArr()[(int)medge->GetPathArr().size() - 1] == node->GetIndex())
						return medge->GetPathArr();
				}
			}
		}
	}

	return vector<int>();
}
#endif