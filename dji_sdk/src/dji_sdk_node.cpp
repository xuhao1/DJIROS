#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <dji_sdk/dji_sdk_node.h>

DJI::onboardSDK::ROSAdapter *rosAdapter;

int main(int argc, char **argv) {
    ros::init(argc, argv, "dji_sdk");
    //ros::NodeHandle nh("dji_sdk");
    ros::NodeHandle nh_private("~");

    //new an object of adapter
    rosAdapter = new DJI::onboardSDK::ROSAdapter;
    std::string uuid = rosAdapter->coreAPI->getVersionData().version_ID;
    if (uuid=="")
    {
        ROS_INFO("Cannot read uuid,use \"fuck\"!");
        uuid = "fuck";
    }
    DJISDKNode* dji_sdk_node = new DJISDKNode(uuid, nh_private);

    ros::AsyncSpinner spinner(4); // Use 4 threads
    spinner.start();
    ros::waitForShutdown();

    //clear
    delete rosAdapter;
    rosAdapter = NULL;
    delete dji_sdk_node;
    dji_sdk_node = NULL;

    return 0;
}
