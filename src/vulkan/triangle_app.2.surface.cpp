#include "../triangle_app.hpp"

void HelloTriangleApplication::createSurface() {
// Actually we don't need the code below, glfw will create surface for us
/*
  VkXlibSurfaceCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
  createInfo.window = glfwGetX11Window(m_window);
  createInfo.dpy = glfwGetX11Display();

  if (vkCreateXlibSurfaceKHR(m_instance, &createInfo, nullptr, &m_surface) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create window surface!");
  }
*/

  if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create windows surface!");
  }
}

void HelloTriangleApplication::cleanVulkanSurface() {
  vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
}

SurfaceProperties HelloTriangleApplication::querySurfaceProperties(const VkPhysicalDevice &physicalDevice) {
  SurfaceProperties details;

  // Query Supported Surface Capabilities
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, m_surface, &details.capabilities);

  // Query Supported Formats
  uint32_t formatCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_surface, &formatCount, nullptr);
  details.formats.resize(formatCount);
  vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_surface, &formatCount, details.formats.data());

  // Query Supported Present Modes
  uint32_t presentModeCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_surface, &presentModeCount, nullptr);
  details.presentModes.resize(presentModeCount);
  vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_surface, &presentModeCount, details.presentModes.data());

  return details;
}