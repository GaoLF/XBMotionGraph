#include "Animation.h"

XBAnimation::XBAnimation()
{
	FrameNum = 0;

	FrameTime = 0.f;


	//FirstPose = new XBPose();

}

void XBAnimation::DownSample(float targetFPS)
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