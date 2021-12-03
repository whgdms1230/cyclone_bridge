
#ifndef CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS2CONFIG_HPP
#define CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS2CONFIG_HPP

#include <string>

namespace cyclone_bridge {

struct ROS2Config
{
  int dds_domain = 100;
  std::string dds_request_topic = "request";
  std::string dds_response_topic = "response";

  void print_config() const;
};

} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS2CONFIG_HPP
