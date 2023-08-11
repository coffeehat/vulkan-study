#include "../triangle_app.hpp"

void HelloTriangleApplication::initVulkan() {
  createInstance();
  createSurface();
  pickPhysicalDevice();
  createLogicalDevice();
  createSwapChain();
}

void HelloTriangleApplication::cleanVulkan() {
  cleanSwapChain();
  cleanVulkanLogicalDevice();
  cleanVulkanSurface();
  cleanVulkanInstance();
}