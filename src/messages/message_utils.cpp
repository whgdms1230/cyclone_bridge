
#include <dds/dds.h>

#include "../dds_utils/common.hpp"

#include "message_utils.hpp"

namespace cyclone_bridge {
namespace messages {

void convert(const Operator& _input, CycloneBridgeData_Operator& _output)
{
  _output.op = _input.op;
}

void convert(const CycloneBridgeData_Operator& _input, Operator& _output)
{
  _output.op = _input.op;
}

void convert(const Variable& _input, CycloneBridgeData_Variable& _output)
{
  _output.var = _input.var;
}

void convert(const CycloneBridgeData_Variable& _input, Variable& _output)
{
  _output.var = _input.var;
}

void convert(const Result& _input, CycloneBridgeData_Result& _output)
{
  _output.msg = common::dds_string_alloc_and_copy(_input.msg);
  _output.ans = _input.ans;
}

void convert(const CycloneBridgeData_Result& _input, Result& _output)
{
  _output.msg = std::string(_input.msg);
  _output.ans = _input.ans;
}

void convert(const Request& _input, CycloneBridgeData_Request& _output)
{
  _output.name = common::dds_string_alloc_and_copy(_input.name);

  size_t ops_size = _input.ops.size();
  _output.ops._maximum = static_cast<uint32_t>(ops_size);
  _output.ops._length = static_cast<uint32_t>(ops_size);
  _output.ops._buffer = dds_sequence_CycloneBridgeData_Operator_allocbuf(ops_size);
  for(size_t i = 0; i < ops_size; ++i)
    convert(_input.ops[i], _output.ops._buffer[i]);
  
  size_t vars_size = _input.vars.size();
  _output.vars._maximum = static_cast<uint32_t>(vars_size);
  _output.vars._length = static_cast<uint32_t>(vars_size);
  _output.vars._buffer = dds_sequence_CycloneBridgeData_Variable_allocbuf(vars_size);
  for(size_t i = 0; i < vars_size; ++i)
    convert(_input.vars[i], _output.vars._buffer[i]);
}

void convert(const CycloneBridgeData_Request& _input, Request& _output)
{
  _output.name = std::string(_input.name);

  _output.ops.clear();
  for(uint32_t i = 0; i < _input.ops._length; ++i)
  {
    Operator tmp;
    convert(_input.ops._buffer[i], tmp);
    _output.ops.push_back(tmp);
  }

  _output.vars.clear();
  for(uint32_t i = 0; i < _input.vars._length; ++i)
  {
    Variable tmp;
    convert(_input.vars._buffer[i], tmp);
    _output.vars.push_back(tmp);
  }
}

void convert(const Response& _input, CycloneBridgeData_Response& _output)
{
  _output.name = common::dds_string_alloc_and_copy(_input.name);
  convert(_input.res, _output.res);
}

void convert(const CycloneBridgeData_Response& _input, Response& _output)
{
  _output.name = std::string(_input.name);
  convert(_input.res, _output.res);
}

} // namespace messages
} // namespace cyclone_bridge
