#include "Pose.h"
#include <vector>
#include <iostream>

using namespace std;

void XBPose::PrintPose()
{
	if (Locations.size() == 0)
	{
		cout << "None" << endl;
	}

	cout << "There are " << Locations.size() << " Joints:" << endl;

	for (int i = 0; i < (int)Locations.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < 3; j++)
		{
			cout << " " << Locations[i];
		}
		for (int j = 0; j < 3; j++)
		{
			cout << " " << Rotations[i];
		}

		cout << endl;
	}
}
