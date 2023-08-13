#include "../triangle_app.hpp"

void HelloTriangleApplication::initVulkan() {
  createInstance();
  createSurface();
  pickPhysicalDevice();
  createLogicalDevice();
  createSwapChain();
  createImageViews();
  createRenderPass();
  createGraphicsPipeline();
}

void HelloTriangleApplication::cleanVulkan() {
  cleanGraphicsPipeline();
  cleanRenderPass();
  cleanImageViews();
  cleanSwapChain();
  cleanLogicalDevice();
  cleanSurface();
  cleanInstance();
}