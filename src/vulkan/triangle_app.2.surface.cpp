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