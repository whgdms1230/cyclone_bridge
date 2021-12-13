
#include <dds/dds.h>

#include <cyclone_bridge/ROS1Bridge.hpp>

#include "ROS1Impl.hpp"

#include "messages/Messages.h"
#include "dds_utils/DDSPublishHandler.hpp"
#include "dds_utils/DDSSubscribeHandler.hpp"

namespace cyclone_bridge {

ROS1Bridge::SharedPtr ROS1Bridge::make(const ROS1Config& _config)
{
  SharedPtr ros1_bridge = SharedPtr(new ROS1Bridge(_config));

  dds_entity_t participant = dds_create_participant(
      static_cast<dds_domainid_t>(_config.dds_domain), NULL, NULL);
  if (participant < 0)
  {
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));
    return nullptr;
  }

  dds::DDSPublishHandler<CycloneBridgeData_Msg>::SharedPtr send_pub(
      new dds::DDSPublishHandler<CycloneBridgeData_Msg>(
          participant, &CycloneBridgeData_Msg_desc,
          _config.dds_ros1_to_ros2_topic));

  dds::DDSSubscribeHandler<CycloneBridgeData_Msg>::SharedPtr 
      read_sub(
          new dds::DDSSubscribeHandler<CycloneBridgeData_Msg>(
              participant, &CycloneBridgeData_Msg_desc,
              _config.dds_ros2_to_ros1_topic));

  if (!send_pub->is_ready() || !read_sub->is_ready())
    return nullptr;

  ros1_bridge->impl->start(ROS1Impl::Fields{
      std::move(participant),
      std::move(send_pub),
      std::move(read_sub)});
  return ros1_bridge;
}

ROS1Bridge::ROS1Bridge(const ROS1Config& _config)
{
  impl.reset(new ROS1Impl(_config));
}

ROS1Bridge::~ROS1Bridge()
{}

bool ROS1Bridge::send(const messages::Msg& ros1_to_ros2_msg)
{
  return impl->send(ros1_to_ros2_msg);
}

bool ROS1Bridge::read(messages::Msg& ros2_to_ros1_msg)
{
  return impl->read(ros2_to_ros1_msg);
}

} // namespace cyclone_bridge
