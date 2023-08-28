#include "../triangle_app.hpp"

#include <algorithm>
#include <set>

void HelloTriangleApplication::pickPhysicalDevice() {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
  if (deviceCount == 0) {
    throw std::runtime_error("Failed to find GPUs with Vulkan support!");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

  for (const auto &device : devices) {
    if (isDeviceSuitable(device)) {
      m_physicalDevice = device;
      break;
    }
  }

  if (m_physicalDevice == VK_NULL_HANDLE) {
    throw std::runtime_error("Failed to find a suitable GPU!");
  }
}

bool HelloTriangleApplication::isDeviceSuitable(const VkPhysicalDevice &physicalDevice) {
  VkPhysicalDeviceProperties deviceProperties;
  VkPhysicalDeviceFeatures deviceFeatures;
  vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
  vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

  // Support Needed Queue Families?
  QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

  // Support Needed Extension?
  bool extensionSupported = checkDeviceExtensionSupport(physicalDevice);

  // Support at Least One Swapchain format?
  bool swapChainAdequate = false;
  SurfaceProperties surfaceProperties = querySurfaceSupportedProperties(physicalDevice);
  if (extensionSupported) {
    swapChainAdequate = !surfaceProperties.formats.empty() && !surfaceProperties.presentModes.empty();
  }

  if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU &&
      deviceFeatures.geometryShader &&
      deviceFeatures.samplerAnisotropy &&
      indices.isComplete() &&
      extensionSupported &&
      swapChainAdequate) {
    m_queueFamilyIndices = indices;
    m_surfaceProperties = surfaceProperties;
    std::cout << "[Physical Device Selection]: Choose " << deviceProperties.deviceName << std::endl;
    return true;
  } else {
    return false;
  }
}

bool HelloTriangleApplication::checkDeviceExtensionSupport(const VkPhysicalDevice &physicalDevice) {
  uint32_t extensionCount;
  vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

  std::set<std::string> requiredExtensions(deviceExtensions.cbegin(), deviceExtensions.cend());
  for (const auto &extension : availableExtensions) {
    std::cout << extension.extensionName << std::endl;
    requiredExtensions.erase(extension.extensionName);
  }
  
  return requiredExtensions.empty();
}

QueueFamilyIndices HelloTriangleApplication::findQueueFamilies(const VkPhysicalDevice &physicalDevice) {
  QueueFamilyIndices indices;
  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

  int i = 0;
  for (const auto &queueFamily : queueFamilies) {
    if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
    }
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, m_surface, &presentSupport);
    if (presentSupport) {
      indices.presentFamily = i;
    }
    if (indices.isComplete()) {
      break;
    }
    ++i;
  }
  
  return indices;
}