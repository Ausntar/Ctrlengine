#pragma once
#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>

#include "stb_image.h"
#include "spdlog/spdlog.h"
namespace cte {
	class CteWindow
	{
	public:
		GLFWwindow* initWindow(std::string title, std::string icon_path = "NULL", int width, int height);
		void GLFWCleanup(GLFWwindow* window);
		void setWindowTitle(GLFWwindow* window, std::string title);
	private:
		std::string title;
        int width;
		int	height;
	};
}//namespace cte
