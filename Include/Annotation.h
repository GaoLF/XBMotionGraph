#ifndef _ANNOTATION_H
#define _ANNOTATION_H

#include <string>
#include <vector>


class XBKeyState
{
public:
	float start;
	float end;
	std::string flag;
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

	void SetStates(std::vector<XBKeyState*>& value)
	{
		states = value;
	}


private:
	std::vector<XBKeyState*> states;

};

#endif // _ANIMATION_H