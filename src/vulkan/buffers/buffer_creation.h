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

void createImage(
    const VkDevice                  &device, 
    const VkPhysicalDevice          &physicalDevice,
    const uint32_t                  width, 
    const uint32_t                  height, 
    const VkFormat                  &format, 
    const VkImageTiling             &tiling, 
    const VkImageUsageFlags         &usage, 
    const VkMemoryPropertyFlags     &properties, 
    VkImage                         *image, 
    VkDeviceMemory                  *imageMemory
);

#endif // __SRC_VULKAN_BUFFERS_BUFFER_CREATION_H__