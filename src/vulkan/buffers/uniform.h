#ifndef __SRC_VULKAN_BUFFERS_UNIFORM_H__
#define __SRC_VULKAN_BUFFERS_UNIFORM_H__

#include <glm/glm.hpp>

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

#endif // __SRC_VULKAN_BUFFERS_UNIFORM_H__