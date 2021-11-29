#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "Pose.h"
#include <vector>

class XBAnimation
{
public:
	XBAnimation();

public:
	//Primary Function

	//Public Function
	vector<XBPose*>& GetAni()
	{
		return Ani;
	}

	vector<XBPose*>& GetAniForCostCalculation()
	{
		return Ani;
	}

	void AddPose(XBPose* pose)
	{
		if (pose)
			Ani.push_back(pose);
	}

	XBPose* GetPose(int index)
	{
		return Ani[index];
	}

	//XBPose* GetFirstPose()
	//{
	//	return FirstPose;
	//}

	int GetFrameNum()
	{
		return FrameNum;
	}

	void SetFrameNum(int value)
	{
		FrameNum = value;
	}

	float GetFrameTime()
	{
		return FrameTime;
	}

	void SetFrameTime(float value)
	{
		FrameTime = value;
	}

	void DownSampleFPS(float targetFPS = FPS);

	bool DownSampleSkeleton(std::vector<bool>);
	//Private Function


private:
	//Private Variable

	int FrameNum;

	//The FPS = 1/FrameTime
	float FrameTime;

	vector<XBPose*> Ani;

	vector<XBPose*> AniForCostCalculation;

	//XBPose* FirstPose;

};

#endif // _ANIMATION_H