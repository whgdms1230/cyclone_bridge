
#ifndef CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__MSG_HPP
#define CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__MSG_HPP

#include <cstdint>

#include "IntNumber.hpp"
#include "StrString.hpp"

namespace cyclone_bridge {
namespace messages {

struct Msg
{
  IntNumber cnt;
  StrString messages;
};

} // namespace messages
} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__MSG_HPP
