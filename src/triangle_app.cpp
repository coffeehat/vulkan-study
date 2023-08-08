#include "triangle_app.hpp"

void HelloTriangleApplication::run() {
  initWindow();
  initVulkan();
  mainLoop();
  cleanup();
}

void HelloTriangleApplication::mainLoop() {
  while (!glfwWindowShouldClose(m_window)) {
    glfwPollEvents();
  }
}

void HelloTriangleApplication::cleanup() {
  cleanVulkan();
  cleanWindow();
}
