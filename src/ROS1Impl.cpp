
#include "ROS1Impl.hpp"

namespace cyclone_bridge {

ROS1Bridge::ROS1Impl::ROS1Impl(const ROS1Config& _config) :
  ros1_config(_config)
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

bool ROS1Bridge::ROS1Impl::send(const messages::IntNumber& ros1_to_ros2_num)
{
  CycloneBridgeData_IntNumber* num = CycloneBridgeData_IntNumber__alloc();
  num->int_num = ros1_to_ros2_num.int_num;

  bool sent = fields.send_pub->write(num);
  CycloneBridgeData_IntNumber_free(num, DDS_FREE_ALL);
  return sent;
}

bool ROS1Bridge::ROS1Impl::read(messages::IntNumber& ros2_to_ros1_num)
{
  auto num = fields.read_sub->read();
  if (!num.empty())
  {
    ros2_to_ros1_num.int_num = num[0]->int_num;
    return true;
  }
  return false;
}

} // namespace cyclone_bridge
