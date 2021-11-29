#ifndef _SKELETON_H
#define _SKELETON_H

#include <vector>
#include <string>

std::vector<std::string> NoitmBVH =
{
	"Hips",
	"RightHips",
	"RightKnee",
	"RightAnkle",
	"LeftHips",
	"LeftKnee",
	"LeftAnkle",
	"Chest",
	"Chest2",
	"Chest3",
	"Neck",
	"Head",
	"RightCollar",
	"RightShoulder",
	"RightElbow",
	"RightWrist",
	"RightFinger0",
	"RightFinger01",
	"RightFinger02",
	"RightFinger1",
	"RightFinger11",
	"RightFinger12",
	"RightFinger2",
	"RightFinger21",
	"RightFinger22",
	"RightFinger3",
	"RightFinger31",
	"RightFinger32",
	"RightFinger4",
	"RightFinger41",
	"RightFinger42",
	"LeftCollar",
	"LeftShoulder",
	"LeftElbow",
	"LeftWrist",
	"LeftFinger0",
	"LeftFinger01",
	"LeftFinger02",
	"LeftFinger1",
	"LeftFinger11",
	"LeftFinger12",
	"LeftFinger2",
	"LeftFinger21",
	"LeftFinger22",
	"LeftFinger3",
	"LeftFinger31",
	"LeftFinger32",
	"LeftFinger4",
	"LeftFinger41",
	"LeftFinger42"
};

std::vector <bool> NoitmBVHMask =
{
	1,//"Hips",
	1,//"RightHips",
	1,//"RightKnee",
	0,//"RightAnkle",
	1,//"LeftHips",
	1,//"LeftKnee",
	0,//"LeftAnkle",
	1,//"Chest",
	1,//"Chest2",
	1,//"Chest3",
	1,//"Neck",
	1,//"Head",
	0,//"RightCollar",
	1,//"RightShoulder",
	1,//"RightElbow",
	1,//"RightWrist",
	0,//"RightFinger0",
	0,//"RightFinger01",
	0,//"RightFinger02",
	0,//"RightFinger1",
	0,//"RightFinger11",
	0,//"RightFinger12",
	0,//"RightFinger2",
	0,//"RightFinger21",
	0,//"RightFinger22",
	0,//"RightFinger3",
	0,//"RightFinger31",
	0,//"RightFinger32",
	0,//"RightFinger4",
	0,//"RightFinger41",
	0,//"RightFinger42",
	0,//"LeftCollar",
	1,//"LeftShoulder",
	1,//"LeftElbow",
	1,//"LeftWrist",
	0,//"LeftFinger0",
	0,//"LeftFinger01",
	0,//"LeftFinger02",
	0,//"LeftFinger1",
	0,//"LeftFinger11",
	0,//"LeftFinger12",
	0,//"LeftFinger2",
	0,//"LeftFinger21",
	0,//"LeftFinger22",
	0,//"LeftFinger3",
	0,//"LeftFinger31",
	0,//"LeftFinger32",
	0,//"LeftFinger4",
	0,//"LeftFinger41",
	0//"LeftFinger42",
};

class XBSkeleton
{
	//Primary Function
public:
	XBSkeleton()
	{

	};

	~XBSkeleton()
	{

	};

	//Public Function

	//Local Function

	//Public Variable

	//Local Variable
private:

};

#endif//_SKELETON_H