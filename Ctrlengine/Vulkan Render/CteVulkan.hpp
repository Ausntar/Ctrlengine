#pragma once
#include "../Window/CteWindow.hpp"
#include "Initialization.hpp"
#include <vulkan/vulkan.h>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <set>

namespace cte {
	class CteVulkan
	{
    public:
		void initVulkan(std::string ApplicationName);
		void cleanup();
	};
}

