#include "Animation.h"

XBAnimation::XBAnimation()
{
	FrameNum = 0;

	FrameTime = 0.f;


	//FirstPose = new XBPose();

}

void XBAnimation::DownSampleFPS(float targetFPS)
{
	float timeinterval = 1.0f / targetFPS;

	int itimes = int(timeinterval / FrameTime + 0.5);

	FrameTime = timeinterval;
	int tmp_iter = 0;
	for (int i = 0; i < (int)Ani.size();)
	{
		if (tmp_iter != 0)
		{
			Ani.erase(Ani.begin() + i);
		}
		else
		{
			i++;
		}
		tmp_iter++;
		if (tmp_iter >= itimes)
		{
			tmp_iter = 0;
		}
	}

	FrameNum = Ani.size();
}

bool XBAnimation::DownSampleSkeleton(vector<bool> SkeletonMask)
{
	int SkeletonMaskSize = (int)SkeletonMask.size();

	AniForCostCalculation.clear();

	for (int i = 0; i < (int)Ani.size(); i++)
	{
		if ((int)Ani[i]->GetLocations().size() != SkeletonMaskSize)
		{
			cerr << "Failed to Down Sample Skeleton." << endl;
			return false;
		}

		XBPose* newCostPose = new XBPose();
		XBPose* oriPose = Ani[i];
		
		newCostPose->SetIndex(oriPose->GetIndex());
		newCostPose->SetName(oriPose->GetName());
		for (int j = 0; j < SkeletonMaskSize; j++)
		{
			if (SkeletonMask[j] == true)
			{
				newCostPose->AddLocation(oriPose->GetLocations()[j]);
				newCostPose->AddRotation(oriPose->GetRotations()[j]);
			}
		}

		AniForCostCalculation.push_back(newCostPose);
	}

	return true;
}