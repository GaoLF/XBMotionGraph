#include "Transition.h"
#include <vector>
#include <iostream>

using namespace std;

XBTransition::XBTransition()
{
	start = 0.f;
	end = 0.f;
}

XBTransition::~XBTransition()
{
	for (int i = 0; i < (int)Paths.size(); i++)
	{
		for (int j = 0; j < (int)(Paths[j].size()); j++)
		{
			delete Paths[i][j];
		}
	}
}