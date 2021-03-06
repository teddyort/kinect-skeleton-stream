// SkeletonStream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/tfMessage.h>
#include <geometry_msgs/PoseArray.h>
#include <windows.h>
#include <NuiApi.h>

using namespace std;
using std::string;

/*
	TODO:
	Make this a class and breakout to functions
	Make Kinect use the near mode or seated mode or both
*/

int _tmain(int argc, _TCHAR * argv[])
{
	//Settings
	char ip[] = "18.242.7.134";
	char base_link[] = "skeleton_frame";

	//Initialize Kinect
	int sensorCount = 0;
	INuiSensor* sensor;
	NUI_SKELETON_FRAME ourframe;
	NUI_SKELETON_BONE_ORIENTATION bone_orientations[NUI_SKELETON_POSITION_COUNT];
	
	while (sensorCount < 1)
	{
		NuiGetSensorCount(&sensorCount);
		printf("Waiting for kinect... Current sensor count: %s\n", to_string(sensorCount).c_str());
	}
	NuiCreateSensorByIndex(0, &sensor);
	sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
	sensor->NuiSkeletonTrackingEnable(NULL, NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT);

	ros::NodeHandle nh;
	char *ros_master = ip;

	printf("Connecting to server at %s\n", ros_master);
	nh.initNode(ros_master);

	printf("Initializing the TF broadcaster\n");
	tf::TransformBroadcaster tf_pub;
	tf_pub.init(nh);

	const int NUM_BONES = 8;
	const int bones_to_send[NUM_BONES] = {
		NUI_SKELETON_POSITION_SHOULDER_CENTER,
		NUI_SKELETON_POSITION_HEAD,
		NUI_SKELETON_POSITION_SHOULDER_LEFT,
		NUI_SKELETON_POSITION_ELBOW_LEFT,
		NUI_SKELETON_POSITION_WRIST_LEFT,
		//NUI_SKELETON_POSITION_HAND_LEFT,
		NUI_SKELETON_POSITION_SHOULDER_RIGHT,
		NUI_SKELETON_POSITION_ELBOW_RIGHT,
		NUI_SKELETON_POSITION_WRIST_RIGHT,
		//NUI_SKELETON_POSITION_HAND_RIGHT,
	};
	const string bones_to_send_names[NUM_BONES] = {
		"shoulder_center",
		"head",
		"shoulder_left",
		"elbow_left",
		"wrist_left",
		//"NUI_SKELETON_POSITION_HAND_LEFT",
		"shoulder_right",
		"elbow_right",
		"wrist_right",
		//"NUI_SKELETON_POSITION_HAND_RIGHT",
	};
	geometry_msgs::TransformStamped tf_joints;
	printf("Go robot go!\n");

	while (1)
	{
		sensor->NuiSkeletonGetNextFrame(0, &ourframe); //Get a frame and stuff it into ourframe
		for (int i = 0; i < NUI_SKELETON_COUNT; i++) //Loop over the 6 possible skeletons
		{
			if (ourframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
			{
				printf("Sending Pose");
				NuiSkeletonCalculateBoneOrientations(&ourframe.SkeletonData[i], bone_orientations);
				for (int j = 0; j < NUM_BONES; j++)
				{
					tf_joints.header.stamp = nh.now();
					tf_joints.header.frame_id = base_link;
					tf_joints.child_frame_id = bones_to_send_names[j].c_str();
					tf_joints.transform.translation.x = ourframe.SkeletonData[i].SkeletonPositions[bones_to_send[j]].x;
					tf_joints.transform.translation.y = ourframe.SkeletonData[i].SkeletonPositions[bones_to_send[j]].y;
					tf_joints.transform.translation.z = ourframe.SkeletonData[i].SkeletonPositions[bones_to_send[j]].z;
					tf_joints.transform.rotation.w = bone_orientations[bones_to_send[j]].absoluteRotation.rotationQuaternion.w;
					tf_joints.transform.rotation.x = bone_orientations[bones_to_send[j]].absoluteRotation.rotationQuaternion.x;
					tf_joints.transform.rotation.y = bone_orientations[bones_to_send[j]].absoluteRotation.rotationQuaternion.y;
					tf_joints.transform.rotation.z = bone_orientations[bones_to_send[j]].absoluteRotation.rotationQuaternion.z;
					tf_pub.sendTransform(tf_joints);
				}
				
			}
		}

		nh.spinOnce();
		Sleep(100);
	}

	printf("All done!\n");
	return 0;
}
