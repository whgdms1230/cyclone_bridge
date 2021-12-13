
#include <dds/dds.h>

#include <cyclone_bridge/ROS2Bridge.hpp>

#include "ROS2Impl.hpp"

#include "messages/Messages.h"
#include "dds_utils/DDSPublishHandler.hpp"
#include "dds_utils/DDSSubscribeHandler.hpp"

namespace cyclone_bridge {

ROS2Bridge::SharedPtr ROS2Bridge::make(const ROS2Config& _config)
{
  SharedPtr ros2_bridge = SharedPtr(new ROS2Bridge(_config));

  dds_entity_t participant = dds_create_participant(
      static_cast<dds_domainid_t>(_config.dds_domain), NULL, NULL);
  if (participant < 0)
  {
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));
    return nullptr;
  }

  dds::DDSSubscribeHandler<CycloneBridgeData_Msg>::SharedPtr read_sub(
      new dds::DDSSubscribeHandler<CycloneBridgeData_Msg>(
          participant, &CycloneBridgeData_Msg_desc,
          _config.dds_ros1_to_ros2_topic));

  dds::DDSPublishHandler<CycloneBridgeData_Msg>::SharedPtr 
      send_pub(
          new dds::DDSPublishHandler<CycloneBridgeData_Msg>(
              participant, &CycloneBridgeData_Msg_desc,
              _config.dds_ros2_to_ros1_topic));

  if (!read_sub->is_ready() || !send_pub->is_ready())
    return nullptr;

  ros2_bridge->impl->start(ROS2Impl::Fields{
      std::move(participant),
      std::move(read_sub),
      std::move(send_pub)});
  return ros2_bridge;
}

ROS2Bridge::ROS2Bridge(const ROS2Config& _config)
{
  impl.reset(new ROS2Impl(_config));
}

ROS2Bridge::~ROS2Bridge()
{}

bool ROS2Bridge::read(messages::Msg& ros1_to_ros2_msg)
{
  return impl->read(ros1_to_ros2_msg);
}

bool ROS2Bridge::send(const messages::Msg& ros2_to_ros1_msg)
{
  return impl->send(ros2_to_ros1_msg);
}

} // namespace cyclone_bridge
