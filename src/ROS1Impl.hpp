
#ifndef CYCLONE_BRIDGE__SRC__ROS1IMPL_HPP
#define CYCLONE_BRIDGE__SRC__ROS1IMPL_HPP

#include <cyclone_bridge/messages/Operator.hpp>
#include <cyclone_bridge/messages/Request.hpp>
#include <cyclone_bridge/messages/Response.hpp>
#include <cyclone_bridge/messages/Result.hpp>
#include <cyclone_bridge/messages/Variable.hpp>

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
    /// DDS participant that is tied to the configured dds_domain_id
    dds_entity_t participant;

    /// DDS publisher that handles sending out current robot states to the 
    /// server
    dds::DDSPublishHandler<CycloneBridgeData_Request>::SharedPtr
        request_pub;

    /// DDS subscriber for mode requests coming from the server
    dds::DDSSubscribeHandler<CycloneBridgeData_Response>::SharedPtr 
        response_sub;
  };

  ROS1Impl(const ROS1Config& config);

  ~ROS1Impl();

  void start(Fields fields);

  bool send_request(const messages::Request& new_request);

  bool read_response(messages::Response& new_response);

private:

  Fields fields;

  ROS1Config client_config;

};

} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__SRC__ROS1IMPL_HPP
