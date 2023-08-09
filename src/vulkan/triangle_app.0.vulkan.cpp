#include "../triangle_app.hpp"

void HelloTriangleApplication::initVulkan() {
  createInstance();
  createSurface();
  pickPhysicalDevice();
  createLogicalDevice();
}

void HelloTriangleApplication::cleanVulkan() {
  cleanVulkanLogicalDevice();
  cleanVulkanSurface();
  cleanVulkanInstance();
}