// SkeletonStream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <NuiApi.h>

using namespace std;

int main()
{
	NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
	NUI_SKELETON_FRAME ourframe;
	while (1) //For all of time
	{
		NuiSkeletonGetNextFrame(0, &ourframe); //Get a frame and stuff it into ourframe
		for (int i = 0; i < 6; i++) //Six times, because the Kinect has space to track six people
		{
			if (ourframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
			{
				cout << "Right Hand: "; //Print "Right hand:"
				cout << ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y << endl;
			}
		}
		//system("cls");//Clear the screen
	}
	NuiShutdown();
    return 0;
}

