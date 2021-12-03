
#ifndef CYCLONE_BRIDGE__SRC__MESSAGES__MESSAGE_UTILS_HPP
#define CYCLONE_BRIDGE__SRC__MESSAGES__MESSAGE_UTILS_HPP

#include <cyclone_bridge/messages/Operator.hpp>
#include <cyclone_bridge/messages/Request.hpp>
#include <cyclone_bridge/messages/Response.hpp>
#include <cyclone_bridge/messages/Result.hpp>
#include <cyclone_bridge/messages/Variable.hpp>

#include "Messages.h"

namespace cyclone_bridge {
namespace messages {

void convert(const Operator& _input, CycloneBridgeData_Operator& _output);

void convert(const CycloneBridgeData_Operator& _input, Operator& _output);

void convert(const Variable& _input, CycloneBridgeData_Variable& _output);

void convert(const CycloneBridgeData_Variable& _input, Variable& _output);

void convert(const Result& _input, CycloneBridgeData_Result& _output);

void convert(const CycloneBridgeData_Result& _input, Result& _output);

void convert(const Request& _input, CycloneBridgeData_Request& _output);

void convert(const CycloneBridgeData_Request& _input, Request& _output);

void convert(const Response& _input, CycloneBridgeData_Response& _output);

void convert(const CycloneBridgeData_Response& _input, Response& _output);

} // namespace 
} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__SRC__MESSAGES__MESSAGE_UTILS_HPP
