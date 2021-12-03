
#ifndef CYCLONE_BRIDGE__SRC__ROS2IMPL_HPP
#define CYCLONE_BRIDGE__SRC__ROS2IMPL_HPP

#include <cyclone_bridge/messages/Operator.hpp>
#include <cyclone_bridge/messages/Request.hpp>
#include <cyclone_bridge/messages/Response.hpp>
#include <cyclone_bridge/messages/Result.hpp>
#include <cyclone_bridge/messages/Variable.hpp>

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

    dds::DDSSubscribeHandler<CycloneBridgeData_Request, 10>::SharedPtr 
        request_sub;

    dds::DDSPublishHandler<CycloneBridgeData_Response>::SharedPtr
        response_pub;

  };

  ROS2Impl(const ROS2Config& config);

  ~ROS2Impl();

  void start(Fields fields);

  bool read_request(messages::Request& new_request);

  bool send_response(const messages::Response& new_response);

private:

  Fields fields;

  ROS2Config server_config;

};

} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__SRC__ROS2IMPL_HPP
