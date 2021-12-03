
#include <cyclone_bridge/ROS2Config.hpp>

#include <cstdio>

namespace cyclone_bridge {

void ROS2Config::print_config() const
{
  printf("ROS 2.0 - ROS 1.0 CYCLONE DDS BRIDGE CONFIGURATION\n");
  printf("  dds domain: %d\n", dds_domain);
  printf("    request topic: %s\n", dds_request_topic.c_str());
  printf("    reponse topic: %s\n", dds_response_topic.c_str());
}

} // namespace cyclone_bridge
