#include "../triangle_app.hpp"

void HelloTriangleApplication::initVulkan() {
  createInstance();
  pickPhysicalDevice();
}

void HelloTriangleApplication::cleanVulkan() {
  cleanVulkanInstance();
}