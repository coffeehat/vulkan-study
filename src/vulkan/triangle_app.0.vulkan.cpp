#include "../triangle_app.hpp"

void HelloTriangleApplication::initVulkan() {
  createInstance();
  pickPhysicalDevice();
  createLogicalDevice();
}

void HelloTriangleApplication::cleanVulkan() {
  cleanVulkanLogicalDevice();
  cleanVulkanInstance();
}