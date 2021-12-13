
#ifndef CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS2CONFIG_HPP
#define CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS2CONFIG_HPP

#include <string>

namespace cyclone_bridge {

struct ROS2Config
{
  int dds_domain = 100;
  std::string dds_ros1_to_ros2_topic = "ros1_to_ros2";
  std::string dds_ros2_to_ros1_topic = "ros2_to_ros1";
};

} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS2CONFIG_HPP
