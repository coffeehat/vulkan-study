/*
Physical Device is like a class
Logical Device is like an instance
*/

#include "../triangle_app.hpp"

void HelloTriangleApplication::createLogicalDevice() {
  VkDeviceQueueCreateInfo queueCreateInfo{};
  queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queueCreateInfo.queueFamilyIndex = m_queueFamilyIndices.graphicsFamily.value();
  queueCreateInfo.queueCount = 1;
  
  float queuePriority = 1.0f;
  queueCreateInfo.pQueuePriorities = &queuePriority;

  VkPhysicalDeviceFeatures deviceFeatures{};
  
  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  
  // Queue Info
  createInfo.queueCreateInfoCount = 1;
  createInfo.pQueueCreateInfos = &queueCreateInfo;
  
  // Feature Enablement Info
  createInfo.pEnabledFeatures = &deviceFeatures;

  // Extension Info
  createInfo.enabledExtensionCount = 0;
  
  // Layer Info
  createInfo.enabledLayerCount = 0;

  if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create logical device!");
  }

  // Queue will be implicitly cleanup when the device is destroyed
  vkGetDeviceQueue(m_device, m_queueFamilyIndices.graphicsFamily.value(), 0, &m_graphicQueue);
}

void HelloTriangleApplication::cleanVulkanLogicalDevice() {
  vkDestroyDevice(m_device, nullptr);
}