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
    drawFrame();
  }

  vkDeviceWaitIdle(m_device);
}

void HelloTriangleApplication::drawFrame() {
  vkWaitForFences(m_device, 1, &m_inFlightFence, VK_TRUE, UINT64_MAX);
  vkResetFences(m_device, 1, &m_inFlightFence);

  uint32_t imageIndex;
  vkAcquireNextImageKHR(m_device, m_swapchain, UINT64_MAX, m_imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

  vkResetCommandBuffer(m_commandBuffer, 0);
  recordCommandBuffer(m_commandBuffer, imageIndex);

  // Submit render command buffer
  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkSemaphore waitSemaphores[] = {m_imageAvailableSemaphore};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &m_commandBuffer;

  VkSemaphore signalSemaphores[] = {m_renderFinishedSemaphore};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  if (vkQueueSubmit(m_graphicQueue, 1, &submitInfo, m_inFlightFence) != VK_SUCCESS) {
      throw std::runtime_error("failed to submit draw command buffer!");
  }

  // Submit present command
  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;

  VkSwapchainKHR swapChains[] = {m_swapchain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &imageIndex;
  presentInfo.pResults = nullptr; // Optional

  vkQueuePresentKHR(m_presentQueue, &presentInfo);
}

void HelloTriangleApplication::cleanup() {
  cleanVulkan();
  cleanWindow();
}
