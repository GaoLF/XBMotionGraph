#ifndef _TYPEDEFINITION_H
#define _TYPEDEFINITION_H

#include <iostream>
#include <vector>
#include <string>

#include <time.h> 

#define DEFAULT_NODE_THRESHOLD (10000.f)

//The Parameter K in the Yang(2020) Paper
#define THRESHOLD_K (int(3))

//two First Frame selection Methods
#define SECTION_RANDOMACESS 1
#define SECTION_ASSIGNED 0

#define INTERVAL_2_IDLE (10.f)

#define FPS (30.0)
#define TIME_INTERVAL (1.f / 30.f)

//The Parameter saved in the Yang(2020) Paper
#define SAVED (100)


enum EMOTION_TYPE
{
	HAPPY = 0,
	ANG   = 1,
	EMOTIONTYPENUM,
};

enum class ACTION_TYPE
{
	IDLE = 0,
	CLAP = 1,
	HUG  = 2,
	ACTIONTYPENUM,
};

const std::string Str_Action_Type[] = {
	"Idle",
	"Clap",
	"Hug",
	"Undefined"
};

//public Function
void split(const std::string& s, std::vector<std::string>& tokens, const std::string& delimiters = " ");

int GetRandomNum(int minv, int maxv);

int GetRandomNum(int maxv);

#endif//_TYPEDEFINITION_H