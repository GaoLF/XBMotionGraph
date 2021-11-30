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

		Eigen::AngleAxisd rollAngle (Eigen::AngleAxisd(pose1->GetLocations()[i][2], Eigen::Vector3d::UnitX()));
		Eigen::AngleAxisd pitchAngle(Eigen::AngleAxisd(pose1->GetLocations()[i][1], Eigen::Vector3d::UnitY()));
		Eigen::AngleAxisd yawAngle  (Eigen::AngleAxisd(pose1->GetLocations()[i][0], Eigen::Vector3d::UnitZ()));

		Eigen::AngleAxisd rollAngle1 (Eigen::AngleAxisd(pose2->GetLocations()[i][2], Eigen::Vector3d::UnitX()));
		Eigen::AngleAxisd pitchAngle1(Eigen::AngleAxisd(pose2->GetLocations()[i][1], Eigen::Vector3d::UnitY()));
		Eigen::AngleAxisd yawAngle1  (Eigen::AngleAxisd(pose2->GetLocations()[i][0], Eigen::Vector3d::UnitZ()));

		Eigen::Quaterniond quaternion, quaternion1;
		quaternion = yawAngle * pitchAngle * rollAngle;
		quaternion1 = yawAngle1 * pitchAngle1 * rollAngle1;

		for (size_t j = 0; j < 3; j++)
		{
			ret += (float)pow(pose1->GetLocations()[i][j] - pose2->GetLocations()[i][j], 2);
		}

		ret += (float)pow(quaternion.x() - quaternion1.x(), 2);
		ret += (float)pow(quaternion.y() - quaternion1.y(), 2);
		ret += (float)pow(quaternion.z() - quaternion1.z(), 2);
	}

	return ret;

}