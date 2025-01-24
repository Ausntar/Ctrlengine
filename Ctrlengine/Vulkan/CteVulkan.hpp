#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <vulkan/vulkan.h>
#include "../model/model.hpp"
#include "../versions/settings/CteManageSettings.hpp"
#include "../versions/window/CteWindow.hpp"
#include "../versions/error/CteError.hpp"
#include <spdlog/spdlog.h>

VkInstance instance;
VkDebugUtilsMessengerEXT debugMessenger;
VkSurfaceKHR surface;
VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
VkDevice device;
VkQueue graphicsQueue;
VkQueue presentQueue;
VkSwapchainKHR swapChain;
std::vector<VkImage> swapChainImages;
VkFormat swapChainImageFormat;
VkExtent2D swapChainExtent;
std::vector<VkImageView> swapChainImageViews;
VkRenderPass renderPass;
VkPipelineLayout pipelineLayout;
VkPipeline graphicsPipeline;
std::vector<VkFramebuffer> swapChainFramebuffers;
VkCommandPool commandPool;
std::vector<VkCommandBuffer> commandBuffers;
VkCommandBuffer commandBuffer;
VkBuffer vertexBuffer;
VkDeviceMemory vertexBufferMemory;
std::vector<VkSemaphore> imageAvailableSemaphores;
std::vector<VkSemaphore> renderFinishedSemaphores;
std::vector<VkFence> inFlightFences;
std::vector<VkFence> imagesInFlight;
size_t currentFrame = 0;
VkImage textureImage;
VkDeviceMemory textureImageMemory;
bool framebufferResized = false;
VkImageView textureImageView;


const int MAX_FRAMES_IN_FLIGHT = 2;
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
namespace cte {
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    class CteVulkan
    {
    public:
        static std::vector<char> readFile(const std::string& filename);
        void createInstance();
        void setupDebugMessenger();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createSurface();
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createGraphicsPipeline();
        void recreateSwapChain();
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffers();
        void createSyncObjects();
        void createVertexBuffer();
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void drawFrame();
        bool initVulkan();
        void closeVulkan();
        void cleanupSwapChain();
    };
    bool isDeviceSuitable(VkPhysicalDevice device);
}
