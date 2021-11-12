#ifndef _TYPEDEFINITION_H
#define _TYPEDEFINITION_H

#define DEFAULT_NODE_THRESHOLD (10000.f)

//The Parameter K in the Yang(2020) Paper
#define THRESHOLD_K (int(3))

enum EMOTION_TYPE
{
	HAPPY = 0,
	ANG   = 1,
	EMOTIONTYPENUM,
};

enum ACTION_TYPE
{
	CLAP = 0,
	HUG  = 1,
	ACTIONTYPENUM,
};


#endif//_TYPEDEFINITION_H