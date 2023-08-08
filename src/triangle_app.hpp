#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

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

  void mainLoop();
  void cleanup();

private:
  void getRequiredInstanceExtensions(
    uint32_t *extCount,
    const char ***exts);

private:
  void cleanWindow();
  void cleanVulkan();

  void cleanVulkanInstance();

private:
  decltype(glfwCreateWindow(0, 0, "", nullptr, nullptr)) window;
  VkInstance instance;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
};