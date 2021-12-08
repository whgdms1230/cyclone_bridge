
#ifndef CYCLONE_BRIDGE__SRC__ROS2IMPL_HPP
#define CYCLONE_BRIDGE__SRC__ROS2IMPL_HPP

#include <cyclone_bridge/messages/IntNumber.hpp>

#include <cyclone_bridge/ROS2Bridge.hpp>
#include <cyclone_bridge/ROS2Config.hpp>

#include <dds/dds.h>

#include "messages/Messages.h"
#include "dds_utils/DDSPublishHandler.hpp"
#include "dds_utils/DDSSubscribeHandler.hpp"

namespace cyclone_bridge {

class ROS2Bridge::ROS2Impl
{
public:

  /// DDS related fields required for the server to operate
  struct Fields
  {
    dds_entity_t participant;

    dds::DDSSubscribeHandler<CycloneBridgeData_IntNumber>::SharedPtr 
        read_sub;

    dds::DDSPublishHandler<CycloneBridgeData_IntNumber>::SharedPtr
        send_pub;
  };

  ROS2Impl(const ROS2Config& config);

  ~ROS2Impl();

  void start(Fields fields);

  bool read(messages::IntNumber& ros1_to_ros2_num);

  bool send(const messages::IntNumber& ros2_to_ros1_num);

private:

  Fields fields;

  ROS2Config ros2_config;

};

} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__SRC__ROS2IMPL_HPP
