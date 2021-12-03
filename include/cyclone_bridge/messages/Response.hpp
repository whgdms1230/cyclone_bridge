
#ifndef CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__RESPONSE_HPP
#define CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__RESPONSE_HPP

#include <string>

#include "Result.hpp"

namespace cyclone_bridge {
namespace messages {

struct Response
{
  std::string name;
  Result res;
};

} // namespace messages
} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__RESPONSE_HPP
