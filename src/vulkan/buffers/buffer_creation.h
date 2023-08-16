#ifndef __SRC_VULKAN_BUFFERS_BUFFER_CREATION_H__
#define __SRC_VULKAN_BUFFERS_BUFFER_CREATION_H__

#include "../../triangle_app.hpp"

void createBuffer(
    const VkDeviceSize              &size, 
    const VkBufferUsageFlags        &usage, 
    const VkMemoryPropertyFlags     &properties, 
    const VkDevice                  &device,
    const VkPhysicalDevice          &physicalDevice,
    VkBuffer                        *buffer, 
    VkDeviceMemory                  *bufferMemory
);

#endif // __SRC_VULKAN_BUFFERS_BUFFER_CREATION_H__