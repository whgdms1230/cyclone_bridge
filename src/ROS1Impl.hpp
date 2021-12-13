
#ifndef CYCLONE_BRIDGE__SRC__ROS1IMPL_HPP
#define CYCLONE_BRIDGE__SRC__ROS1IMPL_HPP

#include <cyclone_bridge/messages/Msg.hpp>

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

    dds::DDSPublishHandler<CycloneBridgeData_Msg>::SharedPtr
        send_pub;

    dds::DDSSubscribeHandler<CycloneBridgeData_Msg>::SharedPtr 
        read_sub;
  };

  ROS1Impl(const ROS1Config& config);

  ~ROS1Impl();

  void start(Fields fields);

  bool send(const messages::Msg& ros1_to_ros2_msg);

  bool read(messages::Msg& ros2_to_ros1_msg);

private:

  Fields fields;

  ROS1Config ros1_config;

};

} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__SRC__ROS1IMPL_HPP
