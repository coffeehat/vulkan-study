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

  void createInstance();

  void mainLoop();
  void cleanup();

private:
  void cleanWindow();
  void cleanVulkan();

  void getRequiredInstanceExtensions(
    uint32_t *extCount,
    const char ***exts);

private:
  decltype(glfwCreateWindow(0, 0, "", nullptr, nullptr)) window;
  VkInstance instance;
};