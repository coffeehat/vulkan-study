cmake_minimum_required(VERSION 3.5)

project(vulkan_study)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

# Find Dependencies
find_package(vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(window_test window_test.cpp)
target_link_libraries(window_test PRIVATE glfw glm::glm vulkan::vulkan)

add_executable(demo
  demo.cpp
  triangle_app.cpp
  glfw/triangle_app.glfw.cpp
  vulkan/triangle_app.vulkan.cpp
  vulkan/triangle_app.instance.cpp
  vulkan/triangle_app.device_selection.cpp)
target_link_libraries(demo PRIVATE glfw glm::glm vulkan::vulkan)
target_compile_features(demo PRIVATE cxx_std_17)