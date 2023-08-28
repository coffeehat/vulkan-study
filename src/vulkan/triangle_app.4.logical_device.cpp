/*
Physical Device is like a class
Logical Device is like an instance
*/

#include "../triangle_app.hpp"

#include <algorithm>
#include <set>
#include <vector>

void HelloTriangleApplication::createLogicalDevice() {
  float queuePriority = 1.0f;
  std::set<uint32_t> uniqueQueueFamilies{m_queueFamilyIndices.graphicsFamily.value(), m_queueFamilyIndices.presentFamily.value()};
  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(uniqueQueueFamilies.size());
  std::transform(
    uniqueQueueFamilies.cbegin(), 
    uniqueQueueFamilies.cend(),
    queueCreateInfos.begin(),
    [&](const uint32_t& queueFamily) {
      VkDeviceQueueCreateInfo createInfo{};
      createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      createInfo.queueFamilyIndex = queueFamily;
      createInfo.queueCount = 1;
      createInfo.pQueuePriorities = &queuePriority;
      return createInfo;
    });

  VkPhysicalDeviceFeatures deviceFeatures{};
  deviceFeatures.samplerAnisotropy = VK_TRUE;
  
  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  
  // Queue Info
  createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
  createInfo.pQueueCreateInfos = queueCreateInfos.data();
  
  // Feature Enablement Info
  createInfo.pEnabledFeatures = &deviceFeatures;

  // Extension Info
  // Why add VK_KHR_swapchain here, rather than vkInstance creation? I don't know
  createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
  createInfo.ppEnabledExtensionNames = deviceExtensions.data();
  
  // Layer Info
  // Preivous implementations of Vulkan made a distinction between instance and device specific validation layers
  // But this is no longer the case
  createInfo.enabledLayerCount = 0;

  if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create logical device!");
  }

  // Queue will be implicitly cleanup when the device is destroyed
  vkGetDeviceQueue(m_device, m_queueFamilyIndices.graphicsFamily.value(), 0, &m_graphicQueue);
  vkGetDeviceQueue(m_device, m_queueFamilyIndices.presentFamily.value(), 0, &m_presentQueue);
}

void HelloTriangleApplication::cleanLogicalDevice() {
  vkDestroyDevice(m_device, nullptr);
}