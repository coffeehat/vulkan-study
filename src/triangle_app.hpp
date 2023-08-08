#ifndef _SRC_TRIANGLE_APP_HPP_
#define _SRC_TRIANGLE_APP_HPP_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;

  bool isComplete() {
    return graphicsFamily.has_value();
  }
};

class HelloTriangleApplication {
public:
  void run();

private:
  void initWindow();
  void initVulkan();

  // Instance Creation
  void createInstance();

  // Device Selection
  void pickPhysicalDevice();

  // Create Logical Device and Queue
  void createLogicalDevice();

  void mainLoop();
  void cleanup();

private:
  void getRequiredInstanceExtensions(
    uint32_t *extCount,
    const char ***exts);

  bool isDeviceSuitable(const VkPhysicalDevice &device);
  QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device);

private:
  void cleanWindow();
  void cleanVulkan();

  void cleanVulkanInstance();
  void cleanVulkanLogicalDevice();

private:
  // GLFW
  decltype(glfwCreateWindow(0, 0, "", nullptr, nullptr)) m_window;
  
  // Vulkan
  VkInstance m_instance;
  
  // Physical device selection related
  VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
  QueueFamilyIndices m_queueFamilyIndices;

  // Logical Device and Queue
  VkDevice m_device;
  VkQueue m_graphicQueue;
};

#endif // _SRC_TRIANGLE_APP_HPP_