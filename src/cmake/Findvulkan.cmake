set(VULKAN_DIR /usr/local/vulkan CACHE PATH "Vulkan directory")

if (WIN32)
  find_path(VULKAN_INCLUDE_DIR vulkan/vulkan.h PATHS ${VULKAN_DIR}/Include NO_CACHE)
  find_library(VULKAN_LIBRARY_PATH vulkan-1.lib PATHS ${VULKAN_DIR}/Lib NO_CACHE)
elseif (UNIX)
  find_path(VULKAN_INCLUDE_DIR vulkan/vulkan.h PATHS ${VULKAN_DIR}/include NO_CACHE)
  find_library(VULKAN_LIBRARY_PATH libvulkan.so PATHS ${VULKAN_DIR}/lib NO_CACHE)
endif ()

# message("vulkan dir: " ${VULKAN_DIR})
# message("vulkan include dir: " ${VULKAN_INCLUDE_DIR})
# message("vulkan library dir: " ${VULKAN_LIBRARY_PATH})

if (NOT VULKAN_INCLUDE_DIR OR NOT VULKAN_LIBRARY_PATH)
  set(VULKAN_DIR VULKAN_DIR-NOTFOUND)
  message(FATAL_ERROR "Cannot find vulkan library, please check the VULKAN_DIR in cache")
else()
  # For imported targets, please see https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html
  add_library(vulkan::vulkan SHARED IMPORTED)
  set_property(TARGET vulkan::vulkan PROPERTY
    IMPORTED_LOCATION ${VULKAN_LIBRARY_PATH})
  set_property(TARGET vulkan::vulkan PROPERTY
    IMPORTED_IMPLIB ${VULKAN_LIBRARY_PATH})
  target_include_directories(vulkan::vulkan INTERFACE ${VULKAN_INCLUDE_DIR})
endif()

# message("vulkan dir: " ${VULKAN_DIR})
# message("vulkan include dir: " ${VULKAN_INCLUDE_DIR})
# message("vulkan library dir: " ${VULKAN_LIBRARY_PATH})