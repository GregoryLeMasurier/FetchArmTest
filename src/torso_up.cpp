#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <control_msgs/FollowJointTrajectoryAction.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "fetch_torso_up");
    ros::NodeHandle nh;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> client("torso_controller/follow_joint_trajectory");
    client.waitForServer();

    trajectory_msgs::JointTrajectoryPoint point;
    point.positions.push_back(0.4);
    point.time_from_start = ros::Duration(5);

    control_msgs::FollowJointTrajectoryGoal goal;
    goal.trajectory.joint_names.push_back("torso_lift_joint");
    goal.trajectory.points.push_back(point);

    client.sendGoal(goal);
    client.waitForResult();
    ROS_INFO_STREAM("MOVED TORSO UP!");

    return 0;
}
