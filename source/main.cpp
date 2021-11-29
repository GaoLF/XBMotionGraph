#include <iostream>
#include "Graph.h"
#include <BVHLoader.h>
using namespace std;

#define FIRST_CONSTRUCT_GRAPH 1
#define LOAD_GRAPH_FROM_EXISTEDDATA 0


int main()
{

	XBBVNProcessor* processor = new XBBVNProcessor();

	XBAnnotation* ann = new XBAnnotation();
	XBAnimation* ani = new XBAnimation();

	XBAnimation* output_ani;
	XBAnnotation* aim_ann = new XBAnnotation();

	//Init the input animation and the input annotation
	ann->LoadJson("Annotation/input1.json");
	processor->LoadBVHFile("Motion/input1.bvh", ani, ann);
	ani->DownSample();
	ann->SetTotalDuration(ani->GetFrameNum() * ani->GetFrameTime());
	ann->AddIdleState();

#if FIRST_CONSTRUCT_GRAPH
	XBGraph* graph = new XBGraph();
	graph->Construction(ani, ann);
	graph->SaveMotionGraphData("Motion/TestMotionGraph1.data");
#elif LOAD_GRAPH_FROM_EXISTEDDATA
	XBGraph* graph = new XBGraph();
	graph->LoadMotionGraphData("Motion/TestMotionGraph1.data");
#endif
	graph->PrintMotionGraph();
	aim_ann->LoadJson("test1.json");
	output_ani = graph->Traverse(aim_ann);
	
	processor->ExportBVHFile("Motion/output1.bvh", ani);
	return 0;
}