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
  createCommandPool();
  createCommandBuffer();
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
  cleanCommandPool();
  cleanCommandBuffer();
}