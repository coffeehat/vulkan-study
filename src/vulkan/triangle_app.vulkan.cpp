#include "../triangle_app.hpp"

void HelloTriangleApplication::initVulkan() {
  createInstance();

}

void HelloTriangleApplication::createInstance() {
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  uint32_t extCount;
  const char **exts;
  getRequiredInstanceExtensions(&extCount, &exts);

  createInfo.enabledExtensionCount = extCount;
  createInfo.ppEnabledExtensionNames = exts;
  createInfo.enabledLayerCount = 0;

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create instance!");
  }
}

void HelloTriangleApplication::cleanVulkan() {
  vkDestroyInstance(instance, nullptr);
}