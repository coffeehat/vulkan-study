#include "../triangle_app.hpp"

#include <algorithm>
#include <vector>

void HelloTriangleApplication::createSwapChain() {
  VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(m_surfaceProperties.formats);
  VkPresentModeKHR presentMode = chooseSwapPresentMode(m_surfaceProperties.presentModes);
  VkExtent2D extent = chooseSwapExtent(m_surfaceProperties.capabilities);

  uint32_t imageCount;
  if (m_surfaceProperties.capabilities.maxImageCount > 0) {
    imageCount = std::clamp(
      m_surfaceProperties.capabilities.minImageCount + 1,
      m_surfaceProperties.capabilities.minImageCount,
      m_surfaceProperties.capabilities.maxImageCount
    );
  } else {
    imageCount = m_surfaceProperties.capabilities.minImageCount + 1;
  }

  VkSwapchainCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface = m_surface;
  createInfo.minImageCount = imageCount;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = extent;
  createInfo.imageArrayLayers = 1; // The amount of layers each image consists of (maybe related to VR?)
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // Swapchain images are used as color attachment

  uint32_t queueFamilyIndices[] = {m_queueFamilyIndices.graphicsFamily.value(), m_queueFamilyIndices.presentFamily.value()};
  if (m_queueFamilyIndices.graphicsFamily != m_queueFamilyIndices.presentFamily) {
    // That is the swapchain are shared by two queue (one write and one read)
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;
  } else {
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0;
    createInfo.pQueueFamilyIndices = nullptr;
  }

  // Certain transforms which should be applied to iamges in the swapchain
  createInfo.preTransform = m_surfaceProperties.capabilities.currentTransform;

  // If the alpha channel should be used for blending with other windows in the window system?
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

  createInfo.presentMode = presentMode;
  // We don't care about the color of pixels that are obscured
  createInfo.clipped = VK_TRUE;
  // Used for supporting resizing window, currently we are fixed window so we don't need to care it
  createInfo.oldSwapchain = VK_NULL_HANDLE;

  if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create swap chain!");
  }

  // Retrieve swapchain images
  vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, nullptr);
  m_swapchainImages.resize(imageCount);
  vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, m_swapchainImages.data());

  m_swapchainImageFormat = surfaceFormat.format;
  m_swapchainExtent = extent;
}

void HelloTriangleApplication::cleanSwapChain() {
  vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
}

VkSurfaceFormatKHR HelloTriangleApplication::chooseSwapSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR> &availableFormats) {
  for (const auto &availableFormat : availableFormats) {
    if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
      availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
        return availableFormat;
      }
  }
  // If failed, it's okay to just settle with the first format that is specified
  return availableFormats[0];
}

/*
VK_PRESENT_MODE_IMMEDIATE_KHR: Images submitted by your application are transferred 
  to the screen right away, which may result in tearing.

VK_PRESENT_MODE_FIFO_KHR: The swap chain is a queue where the display takes an image 
  from the front of the queue when the display is refreshed and the program inserts 
  rendered images at the back of the queue. If the queue is full then the program has 
  to wait. This is most similar to vertical sync as found in modern games. The moment 
  that the display is refreshed is known as "vertical blank".

VK_PRESENT_MODE_FIFO_RELAXED_KHR: This mode only differs from the previous one if 
  the application is late and the queue was empty at the last vertical blank. Instead 
  of waiting for the next vertical blank, the image is transferred right away when it 
  finally arrives. This may result in visible tearing.

VK_PRESENT_MODE_MAILBOX_KHR: This is another variation of the second mode. Instead of 
  blocking the application when the queue is full, the images that are already queued 
  are simply replaced with the newer ones. This mode can be used to render frames as 
  fast as possible while still avoiding tearing, resulting in fewer latency issues than 
  standard vertical sync. This is commonly known as "triple buffering", although the 
  existence of three buffers alone does not necessarily mean that the framerate is 
  unlocked.
*/
VkPresentModeKHR HelloTriangleApplication::chooseSwapPresentMode(
    const std::vector<VkPresentModeKHR> &availablePresentMdoes) {
  for (const auto &availablePresentMdoe : availablePresentMdoes) {
    if (availablePresentMdoe == VK_PRESENT_MODE_MAILBOX_KHR) {
      return availablePresentMdoe;
    }
  }
  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D HelloTriangleApplication::chooseSwapExtent(
    const VkSurfaceCapabilitiesKHR &capabilities) {
  // Use parenthesis here to avoid MSVC build issue
  // Ref: https://stackoverflow.com/a/27443191
  if (capabilities.currentExtent.width != (std::numeric_limits<uint32_t>::max)()) {
    return capabilities.currentExtent;
  } else {
    // if capabilities == maximum value of uint32_t, that is window manager do allow us to differ the resolution
    int width, height;
    /*
      For display, there's two cooridnates system:
      * pixel
      * screen coordinates
      
      For High-DPI display, the pixel resolution is larger than screen coordinates 
      resolution.

      When use GLFW to create window, the window size we give it is screen coordinates.
      We can't just assign this windows size because what vulkan supports is pixel
      So we need the below API `glfwGetFramebufferSize` to query the pixel resolution
      of the created window.
    */
    glfwGetFramebufferSize(m_window, &width, &height);

    VkExtent2D actualExtent = {
      static_cast<uint32_t>(width),
      static_cast<uint32_t>(height)
    };

    actualExtent.width = std::clamp(
      actualExtent.width, 
      capabilities.minImageExtent.width,
      capabilities.maxImageExtent.width
    );
    actualExtent.height = std::clamp(
      actualExtent.height,
      capabilities.minImageExtent.height,
      capabilities.maxImageExtent.height
    );

    return actualExtent;
  }
}