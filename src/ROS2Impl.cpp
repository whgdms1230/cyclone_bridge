
#include "ROS2Impl.hpp"

namespace cyclone_bridge {

ROS2Bridge::ROS2Impl::ROS2Impl(const ROS2Config& _config) :
  ros2_config(_config)
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

bool ROS2Bridge::ROS2Impl::read(messages::IntNumber& ros1_to_ros2_num)
{
  auto num = fields.read_sub->read();
  if (!num.empty())
  {
    ros1_to_ros2_num.int_num = num[0]->int_num;
    return true;
  }
  return false;
}

bool ROS2Bridge::ROS2Impl::send(const messages::IntNumber& ros2_to_ros1_num)
{
  CycloneBridgeData_IntNumber* num = CycloneBridgeData_IntNumber__alloc();
  num->int_num = ros2_to_ros1_num.int_num;

  bool sent = fields.send_pub->write(num);
  CycloneBridgeData_IntNumber_free(num, DDS_FREE_ALL);
  return sent;
}

} // namespace cyclone_bridge
