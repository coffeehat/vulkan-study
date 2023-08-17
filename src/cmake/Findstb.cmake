set(STB_DIR /usr/local/stb CACHE PATH "stb library directory")

find_path(STB_INCLUDE_DIR NAMES stb_include.h stb_image.h PATHS ${STB_DIR} NO_CACHE)

# message("STB DIR: " ${STB_DIR})
# message("STB INCLUDE DIR: " ${STB_INCLUDE_DIR})

if (NOT STB_INCLUDE_DIR)
  set(STB_DIR STB_DIR-NOTFOUND)
  message(FATAL_ERROR "Cannot find stb library, please check the STB_DIR in cache")
else()
  add_library(std INTERFACE)
  target_include_directories(std INTERFACE ${STB_INCLUDE_DIR})
endif()