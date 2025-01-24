#pragma once
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
GLFWwindow* window;
namespace cte {
	

	class CteWindow
	{
	public:
		void initWindow(int width, int height, std::string title);
		void updateWindow();
		void closeWindow();
	};
}
