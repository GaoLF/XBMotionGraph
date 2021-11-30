#ifndef _EDGE_H
#define _EDGE_H

class XBNode;

class XBEdge
{
public:
	XBEdge();
	~XBEdge();

	void SetSrc(XBNode* node)
	{
		Src = node;
	}

	void SetDst(XBNode* node)
	{
		Dst = node;
	}

	XBNode* GetSrc()
	{
		return Src;
	}

	XBNode* GetDst()
	{
		return Dst;
	}

	float GetDist()
	{
		return Dist;
	}

	void SetDist(float value)
	{
		Dist = value;
	}

private:

	XBNode* Src;
	XBNode* Dst;
	float Dist;
};
#endif // _EDGE_H