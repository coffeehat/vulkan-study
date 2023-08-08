#include "../triangle_app.hpp"

#include <vector>
#include <optional>

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;

  bool isComplete() {
    return graphicsFamily.has_value();
  }
};

QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device) {
  QueueFamilyIndices indices;
  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

  int i = 0;
  for (const auto &queueFamily : queueFamilies) {
    if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
    }
    if (indices.isComplete()) {
      break;
    }
    ++i;
  }
  
  return indices;
}

bool isDeviceSuitable(const VkPhysicalDevice &device) {
  VkPhysicalDeviceProperties deviceProperties;
  VkPhysicalDeviceFeatures deviceFeatures;
  vkGetPhysicalDeviceProperties(device, &deviceProperties);
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  QueueFamilyIndices indices = findQueueFamilies(device);

  if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU &&
      deviceFeatures.geometryShader &&
      indices.isComplete()) {
    std::cout << "[Physical Device Selection]: Choose " << deviceProperties.deviceName << std::endl;
    return true;
  } else {
    return false;
  }
}

void HelloTriangleApplication::pickPhysicalDevice() {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
  if (deviceCount == 0) {
    throw std::runtime_error("Failed to find GPUs with Vulkan support!");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  for (const auto &device : devices) {
    if (isDeviceSuitable(device)) {
      physicalDevice = device;
      break;
    }
  }

  if (physicalDevice == VK_NULL_HANDLE) {
    throw std::runtime_error("Failed to find a suitable GPU!");
  }
}