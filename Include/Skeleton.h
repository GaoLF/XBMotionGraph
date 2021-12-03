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


std::vector<std::string> YangBVH =
{
	"Hips",

	"LeftUpLeg",
	"LeftLeg",
	"LeftFoot",
	"LeftToeBase",

	"RightUpLeg",
	"RightLegt",
	"RightFoot",
	"RightToeBase",

	"Spine",
	"Spine1",
	"Spine2",
	"Neck",
	"Head",
	"L_eye_middle",
	"L_eye_end",
	"R_eye_middle",
	"R_eye_end",
	"Head_End",
	"jawTop",
	"jawEnd",

	"LeftShoulder",
	"LeftArm",
	"LeftForeArm",
	"LeftHand",
	"LeftWrist_End",
	"LeftHandIndex1",
	"LeftHandIndex2",
	"LeftHandIndex3",
	"LeftHand4",

	"LeftHandMiddle1",
	"LeftHandMiddle2",
	"LeftHandMiddle3",
	"LeftHandMiddle4",
	"LeftHandRing1",
	"LeftHandRing2",
	"LeftHandRing3",
	"LeftHandRing4",
	"LeftHandPingky1",
	"LeftHandPingky2",
	"LeftHandPingky3",
	"LeftHandPingky4",
	"LeftHandThumb1",
	"LeftHandThumb2",
	"LeftHandThumb3",
	"LeftHandThumb4",

	"RightShoulder",
	"RightArm",
	"RightForeArm",
	"RightForeHand",
	"RightWrist_End",
	"RightIndex1",
	"RightIndex2",
	"RightIndex3",
	"RightIndex4",

	"RightMiddle1",
	"RightMiddle2",
	"RightMiddle3",
	"RightMiddle4",
	"RightRing1",
	"RightRing2",
	"RightRing3",
	"RightRing4",

	"RightPinky1",
	"RightPinky2",
	"RightPinky3",
	"RightPinky4",

	"RightThumb1",
	"RightThumb2",
	"RightThumb3",
	"RightThumb4",

	"BodyNormal"
};


std::vector<bool> YangBVHMask = 
{
	1,//"Hips",

	1,//"LeftUpLeg",
	1,//"LeftLeg",
	1,//"LeftFoot",
	0,//"LeftToeBase",

	1,//"RightUpLeg",
	1,//"RightLegt",
	1,//"RightFoot",
	0,//"RightToeBase",

	1,//Spine",
	1,//"Spine1",
	1,//"Spine2",
	1,//"Neck",
	1,//"Head",
	0,//"L_eye_middle",
	0,//"L_eye_end",
	0,//"R_eye_middle",
	0,//"R_eye_end",
	0,//"Head_End",
	0,//"jawTop",
	0,//"jawEnd",

	1,//"LeftShoulder",
	1,//"LeftArm",
	1,//"LeftForeArm",
	1,//"LeftHand",
	0,//"LeftWrist_End",
	0,//"LeftHandIndex1",
	0,//"LeftHandIndex2",
	0,//"LeftHandIndex3",
	0,//"LeftHand4",

	0,//"LeftHandMiddle1",
	0,//"LeftHandMiddle2",
	0,//"LeftHandMiddle3",
	0,//"LeftHandMiddle4",
	0,//"LeftHandRing1",
	0,//"LeftHandRing2",
	0,//"LeftHandRing3",
	0,//"LeftHandRing4",
	0,//"LeftHandPingky1",
	0,//"LeftHandPingky2",
	0,//"LeftHandPingky3",
	0,//"LeftHandPingky4",
	0,//"LeftHandThumb1",
	0,//"LeftHandThumb2",
	0,//"LeftHandThumb3",
	0,//"LeftHandThumb4",

	1,//"RightShoulder",
	1,//"RightArm",
	1,//"RightForeArm",
	1,//"RightForeHand",
	0,//"RightWrist_End",
	0,//"RightIndex1",
	0,//"RightIndex2",
	0,//"RightIndex3",
	0,//"RightIndex4",

	0,//"RightMiddle1",
	0,//"RightMiddle2",
	0,//"RightMiddle3",
	0,//"RightMiddle4",
	0,//"RightRing1",
	0,//"RightRing2",
	0,//"RightRing3",
	0,//"RightRing4",

	0,//"RightPinky1",
	0,//"RightPinky2",
	0,//"RightPinky3",
	0,//"RightPinky4",

	0,//"RightThumb1",
	0,//"RightThumb2",
	0,//"RightThumb3",
	0,//"RightThumb4",

	0,//"BodyNormal"
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