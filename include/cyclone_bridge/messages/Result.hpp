
#ifndef CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__RESULT_HPP
#define CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__RESULT_HPP

#include <string>

namespace cyclone_bridge {
namespace messages {

struct Result
{
  std::string msg;
  float ans;
};

} // namespace messages
} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__RESULT_HPP
