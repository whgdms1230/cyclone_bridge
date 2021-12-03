
#include "ROS1Impl.hpp"
#include "messages/message_utils.hpp"

namespace cyclone_bridge {

ROS1Bridge::ROS1Impl::ROS1Impl(const ROS1Config& _config) :
  client_config(_config)
{}

ROS1Bridge::ROS1Impl::~ROS1Impl()
{
  dds_return_t return_code = dds_delete(fields.participant);
  if (return_code != DDS_RETCODE_OK)
  {
    DDS_FATAL("dds_delete: %s", dds_strretcode(-return_code));
  }
}

void ROS1Bridge::ROS1Impl::start(Fields _fields)
{
  fields = std::move(_fields);
}

bool ROS1Bridge::ROS1Impl::send_request(const messages::Request& _new_request)
{
  CycloneBridgeData_Request* new_rs = CycloneBridgeData_Request__alloc();
  convert(_new_request, *new_rs);
  bool sent = fields.request_pub->write(new_rs);
  CycloneBridgeData_Request_free(new_rs, DDS_FREE_ALL);
  return sent;
}

bool ROS1Bridge::ROS1Impl::read_response(messages::Response& _new_response)
{
  auto response = fields.response_sub->read();
  if (!response.empty())
  {
    convert(*(response[0]), _new_response);
    return true;
  }
  return false;
}

} // namespace cyclone_bridge
