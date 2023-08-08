#include "../triangle_app.hpp"

void HelloTriangleApplication::initWindow() {
  glfwInit();
  // GLFW_CLIENT_API is the attribute to set, GLFW_NO_API is the value
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // so this is no resizable
  m_window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan demo", nullptr, nullptr);
}

void HelloTriangleApplication::getRequiredInstanceExtensions(
  uint32_t *extCount,
  const char ***exts
) {
  *exts = glfwGetRequiredInstanceExtensions(extCount);
}

void HelloTriangleApplication::cleanWindow() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}