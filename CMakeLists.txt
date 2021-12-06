cmake_minimum_required(VERSION 3.5.0)
project(cyclone_bridge VERSION 0.0.1 LANGUAGES C CXX)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

include(GNUInstallDirs)

find_package(CycloneDDS REQUIRED)

# -----------------------------------------------------------------------------

add_library(cyclone_bridge SHARED
  src/ROS1Bridge.cpp
  src/ROS1Impl.cpp
  src/configs/ROS1Config.cpp
  src/ROS2Bridge.cpp
  src/ROS2Impl.cpp
  src/configs/ROS2Config.cpp
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

# Mark executables and/or libraries for installation
list(APPEND PACKAGE_LIBRARIES
cyclone_bridge
)
install(
  TARGETS ${PACKAGE_LIBRARIES}
  EXPORT cyclone_bridge-targets
  DESTINATION lib
)
install(
  EXPORT cyclone_bridge-targets 
  DESTINATION lib/cmake/cyclone_bridge
)

# Mark cpp header files for installation
install(
  DIRECTORY include/cyclone_bridge
  DESTINATION include
)
install(
  FILES package.xml 
  DESTINATION share/cyclone_bridge
)

# Create cmake config files
# See doc: https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html#example-generating-package-files
include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/cyclone_bridge-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/cyclone_bridge-config.cmake
  INSTALL_DESTINATION lib/cmake/cyclone_bridge
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/cyclone_bridge-config-version.cmake
  VERSION ${PROJECT_VERSION} COMPATIBILITY ExactVersion
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cyclone_bridge-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cyclone_bridge-config-version.cmake
  DESTINATION lib/cmake/cyclone_bridge
)
export(
  EXPORT cyclone_bridge-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/cyclone_bridge-targets.cmake
)
