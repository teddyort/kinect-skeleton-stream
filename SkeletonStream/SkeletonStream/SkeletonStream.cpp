// SkeletonStream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <ros.h>
#include <geometry_msgs/PoseArray.h>
#include <windows.h>
#include <NuiApi.h>

using namespace std;
using std::string;

int _tmain(int argc, _TCHAR * argv[])
{
	NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
	NUI_SKELETON_FRAME ourframe;
	NUI_SKELETON_BONE_ORIENTATION bone_orientations [NUI_SKELETON_POSITION_COUNT];

	ros::NodeHandle nh;
	char *ros_master = "18.242.7.134";

	printf("Connecting to server at %s\n", ros_master);
	nh.initNode(ros_master);

	printf("Advertising joint pose message\n");
	geometry_msgs::PoseArray pose_msg;
	ros::Publisher joint_pose_pub("joint_poses", &pose_msg);
	nh.advertise(joint_pose_pub);

	printf("Go robot go!\n");
	int seq = 0;
	const int NUM_BONES = 6;
	pose_msg.poses_length = NUM_BONES;
	pose_msg.header.frame_id = "map";
	geometry_msgs::Pose mypose [NUM_BONES];
	while (1)
	{
		NuiSkeletonGetNextFrame(0, &ourframe); //Get a frame and stuff it into ourframe
		for (int i = 0; i < NUI_SKELETON_COUNT; i++) //Loop over the 6 possible skeletons
		{
			if (ourframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
			{
				printf("Sending Pose");
				NuiSkeletonCalculateBoneOrientations(&ourframe.SkeletonData[i], bone_orientations);
				for (int j = 0; j < NUM_BONES; j++)
				{
					mypose[j].position.x = ourframe.SkeletonData[i].SkeletonPositions[j].x;
					mypose[j].position.y = ourframe.SkeletonData[i].SkeletonPositions[j].y;
					mypose[j].position.z = ourframe.SkeletonData[i].SkeletonPositions[j].z;
					mypose[j].orientation.w = bone_orientations[j].hierarchicalRotation.rotationQuaternion.w;
					mypose[j].orientation.x = bone_orientations[j].hierarchicalRotation.rotationQuaternion.x;
					mypose[j].orientation.y = bone_orientations[j].hierarchicalRotation.rotationQuaternion.y;
					mypose[j].orientation.z = bone_orientations[j].hierarchicalRotation.rotationQuaternion.z;
				}

				pose_msg.poses = mypose;
				pose_msg.header.seq = seq++;
				joint_pose_pub.publish(&pose_msg);
			}
		}

		nh.spinOnce();
		Sleep(100);
	}

	printf("All done!\n");
	return 0;
}
