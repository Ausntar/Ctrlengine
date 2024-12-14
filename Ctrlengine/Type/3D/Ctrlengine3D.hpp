#pragma once
#include "ObjParsing.hpp"
#include "../../Window/CteWindow.hpp"
VkFormat swapChainImageFormat;
namespace cte {
	class Ctrlengine3D
	{
        public:
			void Renderer3D(std::string obj_path, GLFWwindow* window, std::string ApplicationName);
	};
}


