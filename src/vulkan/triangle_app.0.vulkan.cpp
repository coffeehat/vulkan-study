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
  createFramebuffers();
}

void HelloTriangleApplication::cleanVulkan() {
  cleanFramebuffers();
  cleanGraphicsPipeline();
  cleanRenderPass();
  cleanImageViews();
  cleanSwapChain();
  cleanLogicalDevice();
  cleanSurface();
  cleanInstance();
}