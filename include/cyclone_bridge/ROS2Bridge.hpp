
#ifndef CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS2BRIDGE_HPP
#define CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS2BRIDGE_HPP

#include <memory>
#include <vector>

#include <cyclone_bridge/ROS2Config.hpp>

#include <cyclone_bridge/messages/Msg.hpp>

namespace cyclone_bridge {

class ROS2Bridge
{
public:

  using SharedPtr = std::shared_ptr<ROS2Bridge>;

  static SharedPtr make(const ROS2Config& config);

  bool read(messages::Msg& ros1_to_ros2_msg);

  bool send(const messages::Msg& ros2_to_ros1_msg);

  /// Destructor
  ~ROS2Bridge();

private:

  /// Forward declaration and unique implementation
  class ROS2Impl;

  std::unique_ptr<ROS2Impl> impl;

  ROS2Bridge(const ROS2Config& config);

};

} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS2BRIDGE_HPP
