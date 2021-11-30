#ifndef _TYPEDEFINITION_H
#define _TYPEDEFINITION_H

#include <iostream>
#include <vector>
#include <string>

#include <time.h> 

#define DEFAULT_NODE_THRESHOLD (100000000.f)

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

//ͼ�ı�������1
//·����Ŀ200


//ͼ��traverse������paper��������A*����֧�޽編������ʽ�������֡�
//Method1��һ������ʽ�ķ���,Ҳ����yang���㷨�������ܾ����е�����
//Method2��һ�ִ�BFS�ķ������ǹ���ͼ��ӣ���������path�ȽϿ�ķ���
//��֧�޽編��Ҳֻ��һ�ּ򻯵�BFS����,Ӧ����Ч����õķ���


//��ÿһ�����ֽ���Section
//Section�����֣�Key Section��Transition Section
#define TEST_METHOD_1 0

//��Section����ΪMotion��Ϊstart��peak��end�ķ���
#define TEST_METHOD_2 1



enum EMOTION_TYPE
{
	HAPPY = 0,
	ANG   = 1,
	EMOTIONTYPENUM,
};

enum class ACTION_TYPE
{
	IDLE     = 0,
	CLAP     = 1,
	HUG      = 2,
	WAVEHAND = 3,
	NONE     = 4,
	ACTIONTYPENUM,
};

static bool isKeyAction(ACTION_TYPE action)
{
	if (action >= ACTION_TYPE::ACTIONTYPENUM)
	{
		std::cerr << "Key Action Judgment error!" << std::endl;
		return false;
	}
	else
	{
		if (action == ACTION_TYPE::IDLE || action == ACTION_TYPE::NONE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

//state����������Ϊ���������ַ�������ǻ��߳����Զ�����
//������ʹ�õڶ��ַ���
//state,start,end��annotation�е�����Բ�ͬ
#if TEST_METHOD_2
enum class ACTION_STATE
{
	None  = 0,
	START = 1,
	PEAK  = 2,
	END   = 3,
	STATENUM,
};

//motion edge�����������ָ����һ��motion��start�ģ�ָ����һ��idle motion�ģ������ֶ�����Ч��
//����������Ч�ģ�ָ����һ��motion�ķ�start���֣�ָ��transition���ֵģ�����edge��Ŀ��ֻ��Ϊ��������֡
enum class MOTION_EDGE_TYPE
{
	_2MOTIONSTART = 0,
	_2IDLE        = 1,
	_2None        = 3,
	MOTIONEDGETYPENUM,
};

#define ACTION_START_FRAME_NUM (5)
#define ACTION_END_FRAME_NUM   (5)
#define MOTION_EDGE_FRAMENUM   (15)
#endif

const std::string Str_Action_Type[] = {
	"Idle",
	"Clap",
	"Hug",
	"WaveHand",
	"Undefined"
};

//public Function
void split(const std::string& s, std::vector<std::string>& tokens, const std::string& delimiters = " ");

int GetRandomNum(int minv, int maxv);

int GetRandomNum(int maxv);

//ʱ����ת��Ϊ֡��
static int Time2Frame(float time_value)
{
	float frames_f = time_value * (float)(FPS);
	int ret = (int)(frames_f + 0.5f);
	return ret;
}

//һ��ʱ��ת��Ϊ�ڼ�֡����Ҫ
static int Time2FrameIndex(float time_value)
{
	return Time2Frame(time_value);
}

#endif//_TYPEDEFINITION_H