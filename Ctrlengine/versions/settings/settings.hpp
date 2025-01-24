#pragma once
#include <string>
namespace cte {
	struct EngineSettings {
		std::string gameName = "Ctrlengine";
		double version = 1.2;
		std::string gameType = "3D";
		// 窗口设置
		int windowWidth = 800;
		int windowHeight = 600;

		// 渲染设置
		bool enableVsync = false;
		long long frameRate = 60;
		int tick = 20;
		std::string renderAPI = "Vulkan";
		int MAX_FRAMES_IN_FLIGHT = 2;
		bool enableValidationLayers;

		// 游戏设置
		bool enableDebug = false;
		bool enableConsole = false;
		bool enableMouse = true;

		// 语言设置
		std::string language = "Chinese";

		bool addPackages = true;
	};
}