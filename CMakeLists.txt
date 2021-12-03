cmake_minimum_required(VERSION 3.5.0)
project(cyclone_bridge)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

find_package(CycloneDDS REQUIRED)

install(
  FILES
  src/messages/Messages.idl
  DESTINATION share/cyclone_bridge
  COMPONENT dev)

# -----------------------------------------------------------------------------

add_library(cyclone_bridge SHARED
  src/ROS1Bridge.cpp
  src/ROS1Impl.cpp
  src/configs/ROS1Config.cpp
  src/messages/Messages.c
  src/messages/message_utils.cpp
  src/dds_utils/common.cpp
)

target_include_directories(cyclone_bridge
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(cyclone_bridge
  CycloneDDS::ddsc
  ssl
  crypto
)