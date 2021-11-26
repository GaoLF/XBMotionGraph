#ifndef _GRAPH_H
#define  _GRAPH_H

#include "Edge.h"
#include "Node.h"
#include "Animation.h"
#include "Annotation.h"

class XBMotion;

//ͼ�Ĺ����������Ҫһ��ann(trainann)��ani
//��ͼ����һ���µĶ�������Ҫ��һ��ann(tryann)

class XBGraph
{
public:

	XBGraph();

	~XBGraph();

public:
	//Public Function
	bool Construction(XBAnimation* ani, XBAnnotation* ann);

	XBAnimation* Traverse(XBAnnotation* tryann);

	//Print the Nodes and Edges
	void PrintMotionGraph();

	//Motion Graph Data Format:
	//--------Nodes Number
	//--------//Dst: the edge is Node1->Dst1 and Dist is the distance between them
	//--------Node1 Dst1 Dist1 Dst2 Dist2..
	//--------Node2 Dst1 Dist1 Dst2 Dist3..
	//--------//Nodes Animation Data
	//--------Node1.Index Node1.flag Location Rotation
	bool LoadMotionGraphData(string file);

	//Motion Graph Data Format:
	//--------Nodes Number
	//--------//Dst: the edge is Node1->Dst1 and Dist is the distance between them
	//--------Node1 Dst1 Dist1 Dst2 Dist2..
	//--------Node2 Dst1 Dist1 Dst2 Dist3..
	//--------//Nodes Animation Data
	//--------Node1.Index Node1.flag Location Rotation
	bool SaveMotionGraphData(string file);
	
	vector<XBTransition*>& GetTrans()
	{
		return Trans;
	}

	int GetTransNum()
	{
		return (int)Trans.size();
	}

	
	//Local Function
	int RandomSelectKeySectionIndexInGraph(ACTION_TYPE type);

	XBKeyState* RandomSelectKeyStateInGraph(ACTION_TYPE type);

	//�������ùؼ�Section�ķ���
	//ѡȡ��һ������Ҫ���Section��Ҳ��������demo����Ҫ��
	//��һ���������ѡȡ
	bool TraverseHandleKeySection(XBAnimation* RetAni, XBAnnotation* ann);

	//Handle the all the Trans
	bool TraverseHandleRestSection(XBAnimation* ani, XBAnnotation* ann);
	
	//Handle One Tran 
	//�������start node��end node�浽tran�����annotation��Ҫ�������graph��������
	//���ǰ�trans�浽graph
	bool HandleTran(XBTransition* tran);

	bool ConstructTrans(XBAnnotation* tryann);

#if TEST_METHOD_2
	bool ConstructMotions();

#endif

	bool SetMotionState();


	//Public Variable

	//Local Variable

private:

	vector<XBNode*> Nodes;
	vector<XBEdge*> Edges;

	XBAnimation* Animation;
	XBAnnotation* Annotation;

	//Ϊ����������õ�
	vector<XBTransition*> Trans;

#if TEST_METHOD_2
	vector<XBMotion*> motions;
#endif
};

#endif // _GRAPH_H