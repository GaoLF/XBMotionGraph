#ifndef _BVHLOADER_H
#define _BVHLOADER_H

#include "Animation.h"
#include "Annotation.h"
#include <string>
#include <vector>

//public Function
void split(const std::string& s, std::vector<string>& tokens, const string& delimiters = " ");

enum CHANNEL_FLAG
{
	XPOSITION = 0,
	YPOSITION = 1,
	ZPOSITION = 2,
	XROTATION = 3,
	YROTATION = 4,
	ZROTATION = 5,
	CHANNELFLAGNUM,
};

const string FLAG_STR[6] = {
	"Xposition", "Yposition", "Zposition", "Xrotation", "Yrotation", "Zrotation",
};


class XBBVNLoader
{
public:

	XBBVNLoader();

	//PUBLIC FUNCTION
public:

	bool LoadBVHFile(std::string FileName, XBAnimation* Ani, XBAnnotation* Ann);

	bool ParaseNumberwithChannel(vector<float>& nums, vector<CHANNEL_FLAG>& flags, Eigen::Vector3f& loc, Eigen::Vector3f& rot);


private:

	int skeletelonnum;

};

#endif // _ANIMATION_H