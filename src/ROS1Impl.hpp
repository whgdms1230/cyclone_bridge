
#ifndef CYCLONE_BRIDGE__SRC__ROS1IMPL_HPP
#define CYCLONE_BRIDGE__SRC__ROS1IMPL_HPP

#include <cyclone_bridge/messages/IntNumber.hpp>

#include <cyclone_bridge/ROS1Bridge.hpp>
#include <cyclone_bridge/ROS1Config.hpp>

#include <dds/dds.h>

#include "messages/Messages.h"
#include "dds_utils/DDSPublishHandler.hpp"
#include "dds_utils/DDSSubscribeHandler.hpp"

namespace cyclone_bridge {

class ROS1Bridge::ROS1Impl
{
public:

  /// DDS related fields required for the client to operate
  struct Fields
  {
    dds_entity_t participant;

    dds::DDSPublishHandler<CycloneBridgeData_IntNumber>::SharedPtr
        send_pub;

    dds::DDSSubscribeHandler<CycloneBridgeData_IntNumber>::SharedPtr 
        read_sub;
  };

  ROS1Impl(const ROS1Config& config);

  ~ROS1Impl();

  void start(Fields fields);

  bool send(const messages::IntNumber& ros1_to_ros2_num);

  bool read(messages::IntNumber& ros2_to_ros1_num);

private:

  Fields fields;

  ROS1Config ros1_config;

};

} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__SRC__ROS1IMPL_HPP
