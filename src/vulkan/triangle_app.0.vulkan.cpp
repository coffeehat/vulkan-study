#include "../triangle_app.hpp"

#include <iostream>

void HelloTriangleApplication::initVulkan() {
  std::cout << "Run Create Instance" << std::endl;
  createInstance();
  std::cout << "Run Create Surface" << std::endl;
  createSurface();
  std::cout << "Run Pick Physical Device" << std::endl;
  pickPhysicalDevice();
  std::cout << "Run Create Logical Device" << std::endl;
  createLogicalDevice();
  std::cout << "Run Create Swap Chain" << std::endl;
  createSwapChain();
  std::cout << "Run Create Image Views" << std::endl;
  createSwapchainImageViews();
  std::cout << "Run Create Render Pass" << std::endl;
  createRenderPass();
  std::cout << "Create Descriptor Set Layout" << std::endl;
  createDescriptorSetLayout();
  std::cout << "Run Create Graphics Pipeline" << std::endl;
  createGraphicsPipeline();
  std::cout << "Run Create Frame Buffers" << std::endl;
  createFramebuffers();
  std::cout << "Run Create Command Pool" << std::endl;
  createCommandPool();
  std::cout << "Run Create Texture Image" << std::endl;
  createTextureImage();
  std::cout << "Run Create Texture Image View" << std::endl;
  createTextureImageView();
  std::cout << "Run Create Vertex Buffer" << std::endl;
  createVertexBuffer();
  std::cout << "Run Create Index Buffer" << std::endl;
  createIndexBuffer();
  std::cout << "Create Uniform Buffers" << std::endl;
  createUniformBuffers();
  std::cout << "Create Descriptor Pool" << std::endl;
  createDescriptorPool();
  std::cout << "Create Descriptor Sets" << std::endl;
  createDescriptorSets();
  std::cout << "Run Create Command Buffer" << std::endl;
  createCommandBuffers();
  std::cout << "Run Create Sync Objects" << std::endl;
  createSyncObjects();
}

void HelloTriangleApplication::cleanVulkan() {
  cleanSyncObjects();
  cleanCommandPool();
  cleanFramebuffers();
  cleanGraphicsPipeline();
  cleanRenderPass();
  cleanSwapchainImageViews();
  cleanTextureImageView();
  cleanTextureImage();
  cleanDescriptorPool();
  cleanDescriptorSetLayout();
  cleanSwapChain();
  cleanIndexBuffer();
  cleanVertexBuffer();
  cleanLogicalDevice();
  cleanSurface();
  cleanInstance();
}