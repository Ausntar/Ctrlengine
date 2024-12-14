#include "CteWindow.hpp"
namespace cte {
	GLFWwindow* CteWindow::initWindow(std::string title,std::string icon_path = "NULL", int width, int height) {
		
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		if(!glfwInit()) {
			// 初始化失败
			spdlog::error("GLFW初始化失败");
			return NULL;
		}
		GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window) {
			// 窗口创建失败
			spdlog::error("窗口创建失败");
			glfwTerminate();
			return NULL;
		}
		glfwMakeContextCurrent(window);
		if (icon_path != "NULL") {
			GLFWimage icons[1];
			icons[0].pixels = stbi_load(icon_path.c_str(), &icons[0].width, &icons[0].height, 0, 4); // 使用 stb_image 库加载图标
			glfwWindowHint(GLFW_ICONIFIED, GLFW_TRUE);
			glfwSetWindowIcon(window, 1, icons);
		}
		return window;
	}

	void CteWindow::GLFWCleanup(GLFWwindow* window) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}
	void CteWindow::setWindowTitle(GLFWwindow* window, std::string title) {
		glfwSetWindowTitle(window, title.c_str());
		return;
	}
}
