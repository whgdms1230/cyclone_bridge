
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

  dds::DDSSubscribeHandler<CycloneBridgeData_Request, 10>::SharedPtr request_sub(
      new dds::DDSSubscribeHandler<CycloneBridgeData_Request, 10>(
          participant, &CycloneBridgeData_Request_desc,
          _config.dds_request_topic));

  dds::DDSPublishHandler<CycloneBridgeData_Response>::SharedPtr 
      response_pub(
          new dds::DDSPublishHandler<CycloneBridgeData_Response>(
              participant, &CycloneBridgeData_Response_desc,
              _config.dds_response_topic));

  if (!request_sub->is_ready() || !response_pub->is_ready())
    return nullptr;

  ros2_bridge->impl->start(ROS2Impl::Fields{
      std::move(participant),
      std::move(request_sub),
      std::move(response_pub)});
  return ros2_bridge;
}

ROS2Bridge::ROS2Bridge(const ROS2Config& _config)
{
  impl.reset(new ROS2Impl(_config));
}

ROS2Bridge::~ROS2Bridge()
{}

bool ROS2Bridge::read_request(messages::Request& new_request)
{
  return impl->read_request(new_request);
}

bool ROS2Bridge::send_response(const messages::Response& new_response)
{
  return impl->send_response(new_response);
}

} // namespace cyclone_bridge
