
#include "common.hpp"

#include <dds/dds.h>

namespace cyclone_bridge {
namespace common {

char* dds_string_alloc_and_copy(const std::string& _str)
{
  char* ptr = dds_string_alloc(_str.length());
  for (size_t i = 0; i < _str.length(); ++i)
  {
    ptr[i] = _str[i];
  }
  return ptr;
}

} // namespace common
} // namespace cyclone_bridge
