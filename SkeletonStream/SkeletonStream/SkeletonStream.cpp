// SkeletonStream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <ros.h>
#include <geometry_msgs/PoseStamped.h>
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
	geometry_msgs::PoseStamped pose_msg;
	ros::Publisher joint_pose_pub("joint_poses", &pose_msg);
	nh.advertise(joint_pose_pub);

	printf("Go robot go!\n");
	int seq = 0;
	while (1)
	{
		NuiSkeletonGetNextFrame(0, &ourframe); //Get a frame and stuff it into ourframe
		for (int i = 0; i < NUI_SKELETON_COUNT; i++) //Loop over the 6 possible skeletons
		{
			if (ourframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
			{
				NuiSkeletonCalculateBoneOrientations(&ourframe.SkeletonData[i], bone_orientations);
				pose_msg.pose.orientation.w = bone_orientations[NUI_SKELETON_POSITION_SPINE].hierarchicalRotation.rotationQuaternion.w;
				pose_msg.pose.orientation.x = bone_orientations[NUI_SKELETON_POSITION_SPINE].hierarchicalRotation.rotationQuaternion.x;
				pose_msg.pose.orientation.y = bone_orientations[NUI_SKELETON_POSITION_SPINE].hierarchicalRotation.rotationQuaternion.y;
				pose_msg.pose.orientation.z = bone_orientations[NUI_SKELETON_POSITION_SPINE].hierarchicalRotation.rotationQuaternion.z;
				pose_msg.header.seq = seq++;
				pose_msg.header.frame_id = "map";
				joint_pose_pub.publish(&pose_msg);
			}
		}

		nh.spinOnce();
		Sleep(100);
	}

	printf("All done!\n");
	return 0;
}
