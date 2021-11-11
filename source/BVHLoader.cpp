#include "BVHLoader.h"

#include <fstream>
#include <iostream>

using namespace std;

bool XBBVNLoader::LoadBVHFile(string name, XBAnimation* Ani, XBAnnotation* Ann)
{
	ifstream inFile(name, ios::in);

	if (!inFile) 
	{
		cout << "Can't find this file" << endl;
		return false;
	}

	if (!Ani)
	{
		cout << "Animation not init" << endl;
		return false;
	}

	if (!Ann)
	{
		cout << "Annotation not init!" << endl;
	}

	vector<XBPose*> animation = Ani->GetAni();
	XBPose* FirstPose = Ani->GetFirstPose();

	bool bFirstPose = true;
	char c[40];
	vector<vector<CHANNEL_FLAG>> Channels;
	int CurrentFrameNum = 0;
	vector<float> floatnums;

	while (inFile.getline(c, 40)) 
	{
		string tmp = c;
		if (tmp.find("MOTION") != -1)
		{
			bFirstPose = false;
			animation.push_back(FirstPose);
		}

		//Fill the First Pose
		if (bFirstPose)
		{
			vector<int> channel;
			if (tmp.find("CHANNELS") != -1)
			{
				vector<string> splitstrs;
				vector<CHANNEL_FLAG> nodeflag;
				
				split(tmp, splitstrs, " ");
				vector<CHANNEL_FLAG> tmp_flag_arr;

				for (int i = 0; i < splitstrs.size(); i++)
				{
					for (int j = 0; j < CHANNEL_FLAG::CHANNELFLAGNUM; j++)
					{
						if (splitstrs[i] == FLAG_STR[j])
						{
							tmp_flag_arr.push_back(CHANNEL_FLAG(j));
						}
					}
				}

				Eigen::Vector3f loc, rot;

				ParaseNumberwithChannel(floatnums, tmp_flag_arr, loc, rot);

				Ani->GetFirstPose()->AddLocation(loc);
				Ani->GetFirstPose()->AddRotation(rot);
			}

			if (tmp.find("OFFSET") != -1)
			{
				vector<string> splitstrs;
				split(tmp, splitstrs, " ");
				floatnums.clear();

				for (int i = 0 + 1; i < splitstrs.size(); i++)
				{
					if (float tmp_float = atof(splitstrs[i].c_str()))
					{
						floatnums.push_back(tmp_float);
					}
				}
			}
		}
		//Value the rest Poses
		else
		{
			vector<string> splitstrs;
			split(tmp, splitstrs, " ");

			if (splitstrs[0] == "Frames:")
			{
				int framenum = atoi(splitstrs[1].c_str());
				Ani->SetFrameNum(framenum);
			}
			else if (splitstrs[0] == "Frame Times:")
			{
				float FrameTime = atof(splitstrs[1].c_str());
				Ani->SetFrameTime(FrameTime);
			}
			else
			{
				XBPose* newPose = new XBPose();

				int i = 0;
				int SkeIndex = 0;
				while (i < splitstrs.size())
				{
					int tmp_length = Channels[SkeIndex].size();
					vector<float> tmp_arr;

					//This part can be wrote using the iterator
					//Optimize later..
					for (int j = 0; j < Channels[i].size(); j++)
					{
						if ((i + j) < splitstrs.size())
						{
							float tmp_f = atof(splitstrs[i + j].c_str());
							tmp_arr.push_back(tmp_f);
						}
						
					}

					Eigen::Vector3f loc, rot;
					ParaseNumberwithChannel(tmp_arr, Channels[SkeIndex], loc, rot);

					newPose->AddLocation(loc);
					newPose->AddRotation(rot);

					SkeIndex++;
					i += Channels[i].size();
				}
				CurrentFrameNum++;
			}
		}

	}


	if (CurrentFrameNum != Ani->GetFrameNum())
	{
		cout << "The Frame Number has error!" << endl;
		return false;
	}

	cout << "Succeed to Load the BVH File:" << name << endl;
	inFile.close();
	return true;
}

bool XBBVNLoader::ParaseNumberwithChannel(vector<float>& nums, vector<CHANNEL_FLAG>& flags, Eigen::Vector3f& loc, Eigen::Vector3f& rot)
{
	if (nums.size() == 0 || flags.size() == 0)
		return false;

	for (int i = 0; i < flags.size(); i++)
	{
		int flag = (int)flags[i];
		bool isPos = flag / 3;
		int flagM = flag % 3;

		//nums' length may less than the flags'
		//so this step is necessary.
		if (i < nums.size())
		{
			float num = nums[i];

			if (isPos)
			{
				loc[flagM] = num;
			}
			else
			{
				rot[flagM] = num;
			}
		}	
	}
	
	return true;
}

void split(const string& s, vector<string>& tokens, const string& delimiters = " ")

{
	string::size_type lastPos = s.find_first_not_of(delimiters, 0);

	string::size_type pos = s.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));//use emplace_back after C++11 lastPos = s.find_first_not_of(delimiters, pos);

		pos = s.find_first_of(delimiters, lastPos);

	}

}