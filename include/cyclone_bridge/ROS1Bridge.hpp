
#ifndef CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS1_HPP
#define CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__ROS1_HPP

#include <memory>

#include <cyclone_bridge/ROS1Config.hpp>

#include <cyclone_bridge/messages/Operator.hpp>
#include <cyclone_bridge/messages/Request.hpp>
#include <cyclone_bridge/messages/Response.hpp>
#include <cyclone_bridge/messages/Result.hpp>
#include <cyclone_bridge/messages/Variable.hpp>

namespace cyclone_bridge {

class ROS1Bridge
{
public:

  using SharedPtr = std::shared_ptr<ROS1Bridge>;

  static SharedPtr make(const ROS1Config& config);

  bool send_request(const messages::Request& new_request);

  bool read_response(messages::Response& new_response);

  /// Destructor
  ~ROS1Bridge();

private:

  /// Forward declaration and unique implementation
  class ROS1Impl;

  std::unique_ptr<ROS1Impl> impl;

  ROS1Bridge(const ROS1Config& config);

};

} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__CLIENT_HPP
