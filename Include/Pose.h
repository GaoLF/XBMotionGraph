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

	void SetIndex(int value)
	{
		Index = value;
	}

	int GetIndex()
	{
		return Index;
	}

	void SetName(std::string value)
	{
		Name = value;
	}

	std::string GetName()
	{
		return Name;
	}

	//Local Function

	//Public Variable

	//Local Variable
private:
	string Name;

	vector<Eigen::Vector3f> Rotations;
	vector<Eigen::Vector3f> Locations;

	int Index;
};

#endif//_POSE_H