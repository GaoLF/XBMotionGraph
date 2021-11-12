#ifndef _EDGE_H
#define _EDGE_H

class XBNode;

class XBEdge
{
public:
	XBEdge();

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

private:

	XBNode* Src;
	XBNode* Dst;
};
#endif // _EDGE_H