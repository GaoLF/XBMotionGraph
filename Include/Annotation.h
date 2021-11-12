#ifndef _ANNOTATION_H
#define _ANNOTATION_H

#include <string>
#include <vector>


class XBKeyState
{
public:
	float start;
	float end;
	std::string action;
};

class XBAnnotation
{
public:
	//Primary Function
	XBAnnotation();

	//Public Function
	std::vector<XBKeyState*> GetStates()
	{
		return states;
	}

	XBKeyState* GetState(int index)
	{
		return states[index];
	}

	void SetStates(std::vector<XBKeyState*>& value)
	{
		states = value;
	}

	bool LoadJson(std::string filename);

private:
	std::vector<XBKeyState*> states;

};

#endif // _ANIMATION_H