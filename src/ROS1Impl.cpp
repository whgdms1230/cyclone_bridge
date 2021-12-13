
#include "ROS1Impl.hpp"
#include "dds_utils/common.hpp"

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

bool ROS1Bridge::ROS1Impl::send(const messages::Msg& ros1_to_ros2_msg)
{
  CycloneBridgeData_Msg* msg = CycloneBridgeData_Msg__alloc();
  msg->cnt.int_num = ros1_to_ros2_msg.cnt.int_num;
  msg->messages.messages = common::dds_string_alloc_and_copy(ros1_to_ros2_msg.messages.messages);

  bool sent = fields.send_pub->write(msg);
  CycloneBridgeData_Msg_free(msg, DDS_FREE_ALL);
  return sent;
}

bool ROS1Bridge::ROS1Impl::read(messages::Msg& ros2_to_ros1_msg)
{
  auto msg = fields.read_sub->read();
  if (!msg.empty())
  {
    ros2_to_ros1_msg.cnt.int_num = msg[0]->cnt.int_num;
    ros2_to_ros1_msg.messages.messages = std::string(msg[0]->messages.messages);

    return true;
  }
  return false;
}

} // namespace cyclone_bridge
