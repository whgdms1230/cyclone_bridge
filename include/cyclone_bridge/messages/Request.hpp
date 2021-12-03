
#ifndef CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__REQUEST_HPP
#define CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__REQUEST_HPP

#include <string>
#include <vector>

#include "Operator.hpp"
#include "Variable.hpp"

namespace cyclone_bridge {
namespace messages {

struct Request
{
  std::string name;
  std::vector<Operator> ops;
  std::vector<Variable> vars;
};

} // namespace messages
} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__INCLUDE__CYCLONE_BRIDGE__MESSAGES__REQUEST_HPP
