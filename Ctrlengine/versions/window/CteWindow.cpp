#include "CteWindow.hpp"

namespace cte {
	void CteWindow::initWindow(int width, int height, std::string title) {
		if (!glfwInit()) {
			throw std::runtime_error("failed to initialize GLFW!");
		}
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window) {
			throw std::runtime_error("failed to create GLFW window");
			glfwTerminate();
			return;
		}
	}

	void CteWindow::updateWindow() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void CteWindow::closeWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}
