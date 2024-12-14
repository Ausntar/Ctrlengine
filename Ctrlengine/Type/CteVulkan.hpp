#pragma once
#include "../Window/CteWindow.hpp"
#include <cmath>
VkInstance instance;
VkDevice device;
VkPhysicalDevice physicalDevice;
VkSurfaceKHR surface;
VkCommandPool commandPool;
VkQueue graphicsQueue;
VkSwapchainKHR swapChain;
namespace cte {
	class CteVulkan
	{
    public:
		void initVulkan(std::string ApplicationName);
		void cleanup();
	};
}

