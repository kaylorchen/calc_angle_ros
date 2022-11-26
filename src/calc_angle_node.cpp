#include "math.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"

void Callback(const nav_msgs::Odometry::ConstPtr &msg) {
  double sin_value = msg->pose.pose.orientation.z;
  double cos_value = msg->pose.pose.orientation.w;
  double angle = atan2(sin_value, cos_value);
  // double angle = asin(sin_value);
  // if (sin_value > 0 && cos_value < 0) {
  //   angle = M_PI - angle;
  // } else if (sin_value < 0 && cos_value < 0) {
  //   angle = -M_PI - angle;
  // }
  angle *= 2;
  angle = angle * 180 / M_PI;
  if (angle > 180){
    angle -= 360;
  }else if (angle < -180){
    angle += 360;
  }
  ROS_INFO("angle = %lf, sin = %lf, cos = %lf, x = %lf, y = %lf", angle, sin_value,
           cos_value, msg->pose.pose.position.x, msg->pose.pose.position.y);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub =
      n.subscribe("/my_velocity_controller/odom1", 1000, Callback);
  ros::spin();
  return 0;
}
