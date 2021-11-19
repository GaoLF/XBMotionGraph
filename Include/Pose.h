#ifndef _POSE_H
#define _POSE_H

#include <string>

#include "TypeDefinition.h"
#include "Eigen/Eigen"

using namespace std;


class XBPose
{
public:
	//Primary Function
	XBPose()
	{
		Index = 0;
	};

	~XBPose()
	{

	};

	//Public Function
	vector<Eigen::Vector3f>& GetRotations()
	{
		return Rotations;
	}

	vector<Eigen::Vector3f>& GetLocations()
	{
		return Locations;
	}

	void AddRotation(Eigen::Vector3f value)
	{
		Rotations.push_back(value);
	}

	void AddLocation(Eigen::Vector3f value)
	{
		Locations.push_back(value);
	}

	void PrintPose();

	ACTION_TYPE GetFlag()
	{
		return Flag;
	}

	void SetFlag(ACTION_TYPE value)
	{
		Flag = value;
	}

	void SetIndex(int value)
	{
		Index = value;
	}

	int GetIndex()
	{
		return Index;
	}


	//Local Function

	//Public Variable

	//Local Variable
private:
	string Name;
	ACTION_TYPE Flag;

	vector<Eigen::Vector3f> Rotations;
	vector<Eigen::Vector3f> Locations;

	int Index;

};

#endif//_POSE_H