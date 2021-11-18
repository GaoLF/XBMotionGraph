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
#define FIRST_FRAME_RANDOMACESS 0
#define FIRST_FRAME_ASSIGNED 1

#define INTERVAL_2_IDLE (10.f)

#define FPS (30.0)
#define TIME_INTERVAL (1.f / 30.f)


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


#endif//_TYPEDEFINITION_H