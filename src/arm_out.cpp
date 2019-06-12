#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <moveit/move_group_interface/move_group_interface.h>


int main(int argc, char** argv){
    ros::init(argc, argv, "fetch_arm_out");
    ros::NodeHandle nh;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    moveit::planning_interface::MoveGroupInterface move_fetch("arm_with_torso");

    std::vector<std::string> joints = {"torso_lift_joint", "shoulder_pan_joint", "shoulder_lift_joint", "upperarm_roll_joint",
                       "elbow_flex_joint", "forearm_roll_joint", "wrist_flex_joint", "wrist_roll_joint"};
    std::vector<double> values = {0.36, 1.57, 0, 0.0, -1.7, 0.0, -0.57, 0.0};

    std::map<std::string, double> variable_values;
    for (int i = 0; i < joints.size(); ++i) {
        variable_values[*(joints.begin()+i)] = *(values.begin()+i);
    }
    move_fetch.setJointValueTarget(variable_values);
    move_fetch.move();
    ROS_INFO_STREAM("MOVED ARM OUT!");

    return 0;
}
