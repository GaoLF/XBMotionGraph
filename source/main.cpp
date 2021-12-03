#include <iostream>
#include "Graph.h"
#include <BVHLoader.h>
#include "Skeleton.h"
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

	ann->LoadJson("Annotation/" + input_ann_filename);
	processor->LoadBVHFile("Motion/" + input_bvh_filename, ani, ann);

	ani->DownSampleFPS();
#if OURS
	ani->DownSampleSkeleton(NoitmBVHMask);
#elif YANG
	ani->DownSampleSkeleton(YangBVHMask);
#endif

	ann->SetTotalDuration(ani->GetFrameNum() * ani->GetFrameTime());
	ann->AddIdleState();
	ann->ConstuctStateMap();
	ann->SortStates();

#if FIRST_CONSTRUCT_GRAPH
	XBGraph* graph = new XBGraph();
	graph->Construction(ani, ann);

	graph->SaveMotionGraphData("Motion/" + saved_mg_filename);
#elif LOAD_GRAPH_FROM_EXISTEDDATA
	XBGraph* graph = new XBGraph();
	graph->LoadMotionGraphData("Motion/" + saved_mg_filename);
	graph->SetAnimation(ani);
	graph->SetAnnotation(ann);
#endif

#if TEST_METHOD_2
	graph->ConstructMotions();
#endif

	//graph->PrintMotionGraph();

	aim_ann->LoadJson("Annotation/" + output_ann_filename, true);

	output_ani = graph->Traverse(aim_ann);
	
	processor->ExportBVHFile("Motion/" + output_bvh_filename, output_ani);
	return 0;
}