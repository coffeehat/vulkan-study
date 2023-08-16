cmake_minimum_required(VERSION 3.19)
include(cmake/utils.cmake)
project(vulkan_study)

# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
# if(MSVC)
#   add_link_options(/NODEFAULTLIB:MSVCRT)
# endif()

# Find Dependencies
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Target test
add_executable(window_test window_test.cpp)
target_link_libraries(window_test PRIVATE glfw glm::glm Vulkan::Vulkan)

file(GLOB_RECURSE VULKAN_CORE_FILES "vulkan/*")

# Target demo
add_executable(demo
  demo.cpp
  triangle_app.cpp
  glfw/triangle_app.glfw.cpp
  ${VULKAN_CORE_FILES}
  )
target_link_libraries(demo PRIVATE glfw glm::glm Vulkan::Vulkan)
target_compile_features(demo PRIVATE cxx_std_17)

# - Compile shaders for target demo
file(GLOB_RECURSE GLSL_SOURCE_FILES
  "shaders/*.frag"
  "shaders/*.vert")

set(SHADER_BUILD_PATH "${CMAKE_CURRENT_BINARY_DIR}/shaders")
foreach(GLSL ${GLSL_SOURCE_FILES})
  generate_shader_binname_from_srcname(${GLSL} BIN_NAME)
  set(SPIRV "${SHADER_BUILD_PATH}/${BIN_NAME}")
  # For what is custom command, please see https://zhuanlan.zhihu.com/p/95771200
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_BUILD_PATH}"
    COMMAND Vulkan::glslc ${GLSL} -o ${SPIRV}
  )
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

# For what is custom target, please see https://zhuanlan.zhihu.com/p/95771200
add_custom_target(
  shaders
  DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(demo shaders)

# For visual studio, because of it will create direction for different configuration
# We need to explicit copy the spv file to the configuration destination
add_custom_command(TARGET demo POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:demo>/shaders/"
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SHADER_BUILD_PATH}"
    "$<TARGET_FILE_DIR:demo>/shaders"
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${SHADER_BUILD_PATH}")