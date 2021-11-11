#include <iostream>
#include "Graph.h"
#include <BVHLoader.h>
using namespace std;

int main()
{
	cout << "Hello World" << endl;

	XBBVNLoader* loader = new XBBVNLoader();

	XBAnnotation* ann = new XBAnnotation();
	XBAnimation* ani = new XBAnimation();

	loader->LoadBVHFile("Motion/test1.bvh", ani, ann);

	XBGraph* graph = new XBGraph();
	graph->Construction(ani, ann);
	
	return 0;
}