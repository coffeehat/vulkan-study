#ifndef _SRC_TRIANGLE_APP_HPP_
#define _SRC_TRIANGLE_APP_HPP_

#define VK_USE_PLATFORM_XLIB_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <cstdlib>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> deviceExtensions {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SurfaceProperties {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class HelloTriangleApplication {
public:
  void run();

private:
  void initWindow();
  void initVulkan();

  // Instance Creation
  void createInstance();

  // Surface and swapchain
  void createSurface();

  // Device Selection
  void pickPhysicalDevice();

  // Create Logical Device and Queue
  void createLogicalDevice();

  // Create Swapchain
  void createSwapChain();

  void mainLoop();
  void cleanup();

private:
  void getRequiredInstanceExtensions(
    uint32_t *extCount,
    const char ***exts);

  bool isDeviceSuitable(const VkPhysicalDevice &physicalDevice);
  QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &physicalDevice);
  bool checkDeviceExtensionSupport(const VkPhysicalDevice &physicalDevice);
  SurfaceProperties querySurfaceProperties(const VkPhysicalDevice &physicalDevice);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentMdoes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
private:
  void cleanWindow();
  void cleanVulkan();

  void cleanVulkanInstance();
  void cleanVulkanSurface();
  void cleanSwapChain();
  void cleanVulkanLogicalDevice();

private:
  // GLFW
  decltype(glfwCreateWindow(0, 0, "", nullptr, nullptr)) m_window;
  
  // Vulkan
  VkInstance m_instance;

  // WSI related
  VkSurfaceKHR m_surface;
  VkSwapchainKHR m_swapchain;
  std::vector<VkImage> m_swapchainImages;
  VkFormat m_swapchainImageFormat;
  VkExtent2D m_swapchainExtent;
  SurfaceProperties m_surfaceProperties;
  
  // Physical device selection related
  VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
  QueueFamilyIndices m_queueFamilyIndices;

  // Logical Device and Queue
  VkDevice m_device;
  VkQueue m_graphicQueue;
  VkQueue m_presentQueue;
};

#endif // _SRC_TRIANGLE_APP_HPP_