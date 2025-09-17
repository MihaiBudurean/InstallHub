cmake_minimum_required(VERSION 4.0)
project(InstallHub LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable Qt build automations
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt dependencies
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# === Collect component sources ===
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB COMPONENT_DIRS CONFIGURE_DEPENDS "${SRC_DIR}/*")

set(COMP_SOURCES)
set(COMP_INCLUDES)

foreach(dir IN LISTS COMPONENT_DIRS)
  if(IS_DIRECTORY "${dir}")
    get_filename_component(name "${dir}" NAME)
    set(hpp "${dir}/${name}.hpp")
    set(cpp "${dir}/${name}.cpp")
    if(EXISTS "${cpp}" AND EXISTS "${hpp}")
      list(APPEND COMP_SOURCES "${cpp}" "${hpp}")
      list(APPEND COMP_INCLUDES "${dir}") # so you can #include "Name.hpp"
    endif()
  endif()
endforeach()

# === Components library ===
add_library(installhub_components STATIC ${COMP_SOURCES})
target_include_directories(installhub_components PUBLIC ${COMP_INCLUDES})
target_link_libraries(installhub_components PUBLIC Qt6::Widgets)

# === Main executable ===
qt_add_executable(installhub src/main.cpp)
target_link_libraries(installhub PRIVATE installhub_components)
