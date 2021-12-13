
#ifndef CYCLONE_BRIDGE__SRC__DDS_UTILS__COMMON_HPP
#define CYCLONE_BRIDGE__SRC__DDS_UTILS__COMMON_HPP

#include <string>

namespace cyclone_bridge {
namespace common {

char* dds_string_alloc_and_copy(const std::string& str);

} // namespace common
} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__SRC__DDS_UTILS__COMMON_HPP
