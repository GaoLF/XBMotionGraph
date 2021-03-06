#include "BVHLoader.h"

#include <fstream>
#include <iostream>

using namespace std;

XBBVNProcessor::XBBVNProcessor()
{
	skeletelonnum = 0;
}

bool XBBVNProcessor::LoadBVHFile(string name, XBAnimation* Ani, XBAnnotation* Ann)
{
	ifstream inFile(name, ios::in);

	if (!inFile) 
	{
		cout << "Can't find this file" << endl;
		return false;
	}

	if (!Ani)
	{
		cout << "Animation no initialized" << endl;
		return false;
	}

	if (!Ann)
	{
		cout << "Annotation no initialized!" << endl;
	}

	vector<XBPose*>& animation = Ani->GetAni();
	//XBPose* FirstPose = Ani->GetFirstPose();

	bool bFirstPose = true;
	char c[10000];

	int CurrentFrameNum = 0;
	vector<float> floatnums;

	Channels.clear();

	while (inFile.getline(c, 10000)) 
	{
		string tmp = c;
		if (tmp.find("MOTION") != -1)
		{
			bFirstPose = false;
			//animation.push_back(FirstPose);
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

				for (size_t i = 0; i < splitstrs.size(); i++)
				{
					for (int j = 0; j < CHANNEL_FLAG::CHANNELFLAGNUM; j++)
					{
						if (splitstrs[i] == FLAG_STR[j])
						{
							tmp_flag_arr.push_back(CHANNEL_FLAG(j));
						}
					}
				}

				Eigen::Vector3f loc(0.f, 0.f, 0.f);
				Eigen::Vector3f rot(0.f, 0.f, 0.f);

				ParaseNumberwithChannel(floatnums, tmp_flag_arr, loc, rot);
				Channels.push_back(tmp_flag_arr);
				//Ani->GetFirstPose()->AddLocation(loc);
				//Ani->GetFirstPose()->AddRotation(rot);
			}

			if (tmp.find("OFFSET") != -1)
			{
				vector<string> splitstrs;
				split(tmp, splitstrs, " ");
				floatnums.clear();

				for (size_t i = 0 + 1; i < splitstrs.size(); i++)
				{
					//if (
					float tmp_float = (float)atof(splitstrs[i].c_str());
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
			else if (splitstrs[0] == "Frame")
			{
				float FrameTime = (float)atof(splitstrs[2].c_str());
				Ani->SetFrameTime(FrameTime);
			}
			else if (splitstrs[0] == "MOTION")
			{
				continue;
			}
			else
			{
				XBPose* newPose = new XBPose();

				size_t i = 0;
				int SkeIndex = 0;
				while (i < splitstrs.size())
				{
					int tmp_length = Channels[SkeIndex].size();
					vector<float> tmp_arr;

					//This part can be wrote using the iterator
					//Optimize later..
					for (size_t j = 0; j < Channels[SkeIndex].size(); j++)
					{
						if ((i + j) < splitstrs.size())
						{
							float tmp_f = (float)atof(splitstrs[i + j].c_str());
							tmp_arr.push_back(tmp_f);
						}
						
					}

					Eigen::Vector3f loc(0.f, 0.f, 0.f);
					Eigen::Vector3f rot(0.f, 0.f, 0.f);
					ParaseNumberwithChannel(tmp_arr, Channels[SkeIndex], loc, rot);

					newPose->AddLocation(loc);
					newPose->AddRotation(rot);
					i += Channels[SkeIndex].size();
					SkeIndex++;
				}

				animation.push_back(newPose);
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


bool XBBVNProcessor::ExportBVHFile(string name, XBAnimation* Ani)
{
	if (Ani == NULL)
	{
		cerr << "Export error, bad point" << endl;
	}

	ofstream outFile(name);

	if (!outFile)
	{
		cout << "Init the output file error" << endl;
		return false;
	}

	string OutStrs;

	OutStrs = "MOTION\n";
	//char FrameNum[20];
	//char FrameTime[20];

	//itoa(Ani->GetFrameNum(), FrameNum, 10);
	//gcvt(Ani->GetFrameTime(), FrameTime);

	OutStrs += ("Frames: " + to_string(Ani->GetFrameNum()) + "\n");
	OutStrs += ("Frame Time: " + to_string(Ani->GetFrameTime()) + "\n");

	vector<XBPose*> Poses = Ani->GetAni();
	for (int i = 0; i < Ani->GetFrameNum(); i++)
	{
		XBPose* Pose = Poses[i];

		string tmp = "";

		if (Pose->GetLocations().size() != Pose->GetRotations().size()) {
			cerr << "" << endl;
			return false;
		}


		int length = (int)Pose->GetLocations().size();

		for (int j = 0; j < length; j++)
		{
			for (int index = 0; index < 6; index++)
			{
				CHANNEL_FLAG flag = Channels[j][index];

				if (flag == CHANNEL_FLAG::XPOSITION)
					tmp += to_string(Pose->GetLocations()[j][0]) + " ";
				else if (flag == CHANNEL_FLAG::YPOSITION)
					tmp += to_string(Pose->GetLocations()[j][1]) + " ";
				else if (flag == CHANNEL_FLAG::ZPOSITION)
					tmp += to_string(Pose->GetLocations()[j][2]) + " ";
				else if (flag == CHANNEL_FLAG::XROTATION)
					tmp += to_string(Pose->GetRotations()[j][0]) + " ";
				else if (flag == CHANNEL_FLAG::YROTATION)
					tmp += to_string(Pose->GetRotations()[j][1]) + " ";
				else if (flag == CHANNEL_FLAG::ZROTATION)
					tmp += to_string(Pose->GetRotations()[j][2]) + " ";

			}

			//tmp += (to_string(Pose->GetLocations()[j][0]) + " " + to_string(Pose->GetLocations()[j][1])
			//	+ " "  + to_string(Pose->GetLocations()[j][2]) + " ");

			//tmp += (to_string(Pose->GetRotations()[j][2]) + " " + to_string(Pose->GetRotations()[j][1])
			//	+ " "  + to_string(Pose->GetRotations()[j][0]) + " ");
		}
		tmp += "\n";

		OutStrs += tmp;
	}
	
	cout << "Succeed to Export the BVH File: " + name << endl;

	outFile << OutStrs;
	outFile.close();

	return true;

}

bool XBBVNProcessor::ParaseNumberwithChannel(vector<float>& nums, vector<CHANNEL_FLAG>& flags, Eigen::Vector3f& loc, Eigen::Vector3f& rot)
{
	if (nums.size() == 0 || flags.size() == 0)
		return false;

	for (size_t i = 0; i < flags.size(); i++)
	{
		int flag = (int)flags[i];
		bool isPos = !(flag / 3);
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

