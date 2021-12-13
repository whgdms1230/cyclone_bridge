
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

bool ROS2Bridge::ROS2Impl::read(messages::Msg& ros1_to_ros2_msg)
{
  auto msg = fields.read_sub->read();
  if (!msg.empty())
  {
    ros1_to_ros2_msg.cnt.int_num = msg[0]->cnt.int_num;
    return true;
  }
  return false;
}

bool ROS2Bridge::ROS2Impl::send(const messages::Msg& ros2_to_ros1_msg)
{
  CycloneBridgeData_Msg* msg = CycloneBridgeData_Msg__alloc();
  msg->cnt.int_num = ros2_to_ros1_msg.cnt.int_num;

  bool sent = fields.send_pub->write(msg);
  CycloneBridgeData_Msg_free(msg, DDS_FREE_ALL);
  return sent;
}

} // namespace cyclone_bridge
