#ifndef _SRC_TRIANGLE_APP_HPP_
#define _SRC_TRIANGLE_APP_HPP_

/*
    __linux__       Defined on Linux
    __sun           Defined on Solaris
    __FreeBSD__     Defined on FreeBSD
    __NetBSD__      Defined on NetBSD
    __OpenBSD__     Defined on OpenBSD
    __APPLE__       Defined on Mac OS X
    __hpux          Defined on HP-UX
    __osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
    __sgi           Defined on Irix
    _AIX            Defined on AIX
    _WIN32          Defined on Windows
*/

#ifdef _WIN32
  #define VK_USE_PLATFORM_WIN32_KHR
  #define GLFW_INCLUDE_VULKAN
  #include <GLFW/glfw3.h>
  
  #define GLFW_EXPOSE_NATIVE_WIN32
  #include <GLFW/glfw3native.h>
#elif __linux__
  #define VK_USE_PLATFORM_XLIB_KHR
  #define GLFW_INCLUDE_VULKAN
  #include <GLFW/glfw3.h>

  #define GLFW_EXPOSE_NATIVE_X11
  #include <GLFW/glfw3native.h>
#endif

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> deviceExtensions {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SurfaceProperties {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class HelloTriangleApplication {
public:
  void run();

private:
  void initWindow();
  void initVulkan();

  // Instance Creation
  void createInstance();

  // Surface
  void createSurface();

  // Device Selection
  void pickPhysicalDevice();

  // Create Logical Device and Queue
  void createLogicalDevice();

  // Create Swapchain
  void createSwapChain();

  // Create Image Views
  void createImageViews();

  // Create Render Pass
  void createRenderPass();

  // Create Graphics Pipeline
  void createGraphicsPipeline();

  // Create Frame Buffers
  void createFramebuffers();

  // Create Command Pool
  void createCommandPool();
  
  // Create Command Buffer
  void createCommandBuffer();

  void createSyncObjects();

  void mainLoop();
  void drawFrame();
  void cleanup();

private:
  void getRequiredInstanceExtensions(
    uint32_t *extCount,
    const char ***exts);

  bool checkValidationLayerSupport();
  bool isDeviceSuitable(const VkPhysicalDevice &physicalDevice);
  QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &physicalDevice);
  bool checkDeviceExtensionSupport(const VkPhysicalDevice &physicalDevice);
  SurfaceProperties querySurfaceSupportedProperties(const VkPhysicalDevice &physicalDevice);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentMdoes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
  VkShaderModule createShaderModule(const std::vector<char> &code);
  void recordCommandBuffer(VkCommandBuffer &commandBuffer, uint32_t imageIndex);

private:
  void cleanWindow();
  void cleanVulkan();

  void cleanInstance();
  void cleanSurface();
  void cleanLogicalDevice();
  void cleanSwapChain();
  void cleanImageViews();

  void cleanRenderPass();
  void cleanGraphicsPipeline();
  void cleanFramebuffers();
  void cleanCommandPool();
  void cleanCommandBuffer();
  void cleanSyncObjects();
private:
  // GLFW
  decltype(glfwCreateWindow(0, 0, "", nullptr, nullptr)) m_window;
  
  // Vulkan
  VkInstance m_instance;

  // WSI related
  // - surface
  VkSurfaceKHR m_surface;
  SurfaceProperties m_surfaceProperties;
  // - swapchain
  VkSwapchainKHR m_swapchain;
  std::vector<VkImage> m_swapchainImages;
  VkFormat m_swapchainImageFormat;
  VkExtent2D m_swapchainExtent;
  // - swapchain imageviews
  std::vector<VkImageView> m_swapchainImageViews;
  
  // Physical device selection related
  VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
  QueueFamilyIndices m_queueFamilyIndices;

  // Logical Device and Queue
  VkDevice m_device;
  VkQueue m_graphicQueue;
  VkQueue m_presentQueue;

  // Render Pass
  VkRenderPass m_renderPass;

  // Pipeline Layout
  VkPipelineLayout m_pipelineLayout;

  // Graphic Pipeline
  VkPipeline m_graphicsPipeline;

  // Framebuffer
  std::vector<VkFramebuffer> m_swapchainFramebuffers;

  // Command Pool
  VkCommandPool m_commandPool;

  // Command Buffer
  VkCommandBuffer m_commandBuffer;

  // Semaphore
  VkSemaphore m_imageAvailableSemaphore;
  VkSemaphore m_renderFinishedSemaphore;
  VkFence m_inFlightFence;
};

#endif // _SRC_TRIANGLE_APP_HPP_