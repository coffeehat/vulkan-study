#include "../triangle_app.hpp"

#include <array>

void HelloTriangleApplication::createDescriptorSetLayout() {
    /*
    A descriptor is a way for shaders to freely access resources like buffers and images
    This descriptor is to hold the uniform buffer
    Usage of descriptors consists of three parts:
    * Specify a descriptor layout during pipeline creation
    * Allocate a descriptor set from a descriptor pool
    * Bind the descriptor set during rendering

    The descriptor layout specifies the type of resources that are going to be accesses by the pipeline
    A descriptor set specifies the actual buffer or image resources that will be bound to the descriptors
    */
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1; // Specifies the number of values in the array (could used to specify a transformation for each of the bones in a skeleton for skeletal animation)
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

    VkDescriptorSetLayoutBinding samplerLayoutBinding{};
    samplerLayoutBinding.binding = 1;
    samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerLayoutBinding.descriptorCount = 1;
    samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    samplerLayoutBinding.pImmutableSamplers = nullptr;

    std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();

    if (vkCreateDescriptorSetLayout(m_device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

void HelloTriangleApplication::cleanDescriptorSetLayout() {
    vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);
}