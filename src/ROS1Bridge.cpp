
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

  dds::DDSPublishHandler<CycloneBridgeData_Request>::SharedPtr request_pub(
      new dds::DDSPublishHandler<CycloneBridgeData_Request>(
          participant, &CycloneBridgeData_Request_desc,
          _config.dds_request_topic));

  dds::DDSSubscribeHandler<CycloneBridgeData_Response>::SharedPtr 
      response_sub(
          new dds::DDSSubscribeHandler<CycloneBridgeData_Response>(
              participant, &CycloneBridgeData_Response_desc,
              _config.dds_response_topic));

  if (!request_pub->is_ready() || !response_sub->is_ready())
    return nullptr;

  ros1_bridge->impl->start(ROS1Impl::Fields{
      std::move(participant),
      std::move(request_pub),
      std::move(response_sub)});
  return ros1_bridge;
}

ROS1Bridge::ROS1Bridge(const ROS1Config& _config)
{
  impl.reset(new ROS1Impl(_config));
}

ROS1Bridge::~ROS1Bridge()
{}

bool ROS1Bridge::send_request(const messages::Request& new_request)
{
  return impl->send_request(new_request);
}

bool ROS1Bridge::read_response(messages::Response& new_response)
{
  return impl->read_response(new_response);
}

} // namespace cyclone_bridge
