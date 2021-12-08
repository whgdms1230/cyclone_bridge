
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

  dds::DDSSubscribeHandler<CycloneBridgeData_IntNumber>::SharedPtr read_sub(
      new dds::DDSSubscribeHandler<CycloneBridgeData_IntNumber>(
          participant, &CycloneBridgeData_IntNumber_desc,
          _config.dds_ros1_to_ros2_topic));

  dds::DDSPublishHandler<CycloneBridgeData_IntNumber>::SharedPtr 
      send_pub(
          new dds::DDSPublishHandler<CycloneBridgeData_IntNumber>(
              participant, &CycloneBridgeData_IntNumber_desc,
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

bool ROS2Bridge::read(messages::IntNumber& ros1_to_ros2_num)
{
  return impl->read(ros1_to_ros2_num);
}

bool ROS2Bridge::send(const messages::IntNumber& ros2_to_ros1_num)
{
  return impl->send(ros2_to_ros1_num);
}

} // namespace cyclone_bridge
