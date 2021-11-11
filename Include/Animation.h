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

	XBPose* GetFirstPose()
	{
		return FirstPose;
	}

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

	//Private Function


private:
	//Private Variable

	int FrameNum;

	//The FPS = 1/FrameTime
	float FrameTime;

	vector<XBPose*> Ani;

	XBPose* FirstPose;

};

#endif // _ANIMATION_H