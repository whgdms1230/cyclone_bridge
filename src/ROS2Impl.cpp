
#include "ROS2Impl.hpp"
#include "messages/message_utils.hpp"

namespace cyclone_bridge {

ROS2Bridge::ROS2Impl::ROS2Impl(const ROS2Config& _config) :
  server_config(_config)
{}

ROS2Bridge::ROS2Impl::~ROS2Impl()
{
  dds_return_t return_code = dds_delete(fields.participant);
  if (return_code != DDS_RETCODE_OK)
  {
    DDS_FATAL("dds_delete: %s", dds_strretcode(-return_code));
  }
}

void ROS2Bridge::ROS2Impl::start(Fields _fields)
{
  fields = std::move(_fields);
}

bool ROS2Bridge::ROS2Impl::read_request(messages::Request& _new_request)
{
  auto request = fields.request_sub->read();
  if (!request.empty())
  {
    convert(*(request[i]), _new_request);
    return true;
  }
  return false;
}

bool ROS2Bridge::ROS2Impl::send_response(const messages::Response& _new_response)
{
  CycloneBridgeData_Response* new_rs = CycloneBridgeData_Response__alloc();
  convert(_new_response, *new_rs);
  bool sent = fields.response_pub->write(new_rs);
  CycloneBridgeData_Response_free(new_rs, DDS_FREE_ALL);
  return sent;
}

} // namespace cyclone_bridge
