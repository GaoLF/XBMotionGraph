#include <iostream>
#include "Graph.h"
#include <BVHLoader.h>
using namespace std;

int main()
{
	cout << "Hello World" << endl;

	XBBVNProcessor* processor = new XBBVNProcessor();

	XBAnnotation* ann = new XBAnnotation();
	XBAnimation* ani = new XBAnimation();

	XBAnimation* output_ani;
	XBAnnotation* aim_ann = new XBAnnotation();

	ann->LoadJson("Annotation/input1.json");
	processor->LoadBVHFile("Motion/input1.bvh", ani, ann);

	XBGraph* graph = new XBGraph();
	graph->Construction(ani, ann);
	graph->PrintMotionGraph();
	//aim_ann->LoadJson("test1.json");
	//output_ani = graph->Traverse(aim_ann);
	
	processor->ExportBVHFile("Motion/output1.bvh", ani);
	return 0;
}