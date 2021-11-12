#include "Cost.h"
#include <iostream>
#include <math.h>
using namespace std;

XBCost::XBCost()
{

}

float XBCost::Dist(XBPose* pose1, XBPose* pose2)
{
	
	if (pose1 == NULL || pose2 == NULL)
	{
		cerr << "Dist Calculation error! pose is bad point" << endl;
		return -1.f;
	}

	size_t length = pose1->GetLocations().size();

	if ((pose2->GetLocations().size() != length) || (pose1->GetRotations().size() != length) ||
		(pose2->GetRotations().size() != length))
	{
		cerr << "Dist Calculation error! Sth is wrong with the poses' length" << endl;
		return -1.f;
	}

	float ret = 0;
	for (size_t i = 0; i < length; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			ret += (float)pow(pose1->GetLocations()[i][j] - pose2->GetLocations()[i][j], 2);
			ret += (float)pow(pose1->GetRotations()[i][j] - pose2->GetRotations()[i][j], 2);
		}
	}

	return ret;

}