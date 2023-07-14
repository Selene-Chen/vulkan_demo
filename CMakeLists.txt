cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(vulkan_demo LANGUAGES CXX)

include(cmake/findsdl2.cmake)
find_package(Vulkan REQUIRED)

# add_subdirectory(toy2d)
add_subdirectory(sanbox)
