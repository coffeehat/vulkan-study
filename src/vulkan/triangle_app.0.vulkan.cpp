#include "../triangle_app.hpp"

void HelloTriangleApplication::initVulkan() {
  createInstance();
  createSurface();
  pickPhysicalDevice();
  createLogicalDevice();
  createSwapChain();
  createImageViews();
}

void HelloTriangleApplication::cleanVulkan() {
  cleanImageViews();
  cleanSwapChain();
  cleanLogicalDevice();
  cleanSurface();
  cleanInstance();
}