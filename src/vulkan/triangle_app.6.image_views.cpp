#include "../triangle_app.hpp"

#include <algorithm>

void HelloTriangleApplication::createSwapchainImageViews() {
  m_swapchainImageViews.resize(m_swapchainImages.size());
  std::transform(
    m_swapchainImages.cbegin(),
    m_swapchainImages.cend(),
    m_swapchainImageViews.begin(),
    [&](const VkImage& image) {
      VkImageView imageView;
      //TODO: image view pointer passed into createImageView should point directly to the m_swapchainImageViews' elements
      createImageView(image, m_swapchainImageFormat, &imageView);
      return imageView;
    });
}

void HelloTriangleApplication::createImageView(
    const VkImage &image,
    const VkFormat &format,
    VkImageView *imageView
) {
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.image = image;
    createInfo.format = format;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

// We can just omit the below settings because SWIZZLE_IDENTITY is already 0
//   createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
//   createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
//   createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
//   createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    if (vkCreateImageView(m_device, &createInfo, nullptr, imageView) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create texture image view!");
    }
}

void HelloTriangleApplication::cleanSwapchainImageViews() {
  std::for_each(
    m_swapchainImageViews.begin(),
    m_swapchainImageViews.end(),
    [&](VkImageView &imageView) {
      vkDestroyImageView(m_device, imageView, nullptr);
    });
}