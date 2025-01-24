#pragma once
#include <string>
namespace cte {
	struct EngineSettings {
		std::string gameName = "Ctrlengine";
		double version = 1.2;
		std::string gameType = "3D";
		// ��������
		int windowWidth = 800;
		int windowHeight = 600;

		// ��Ⱦ����
		bool enableVsync = false;
		long long frameRate = 60;
		int tick = 20;
		std::string renderAPI = "Vulkan";
		int MAX_FRAMES_IN_FLIGHT = 2;
		bool enableValidationLayers;

		// ��Ϸ����
		bool enableDebug = false;
		bool enableConsole = false;
		bool enableMouse = true;

		// ��������
		std::string language = "Chinese";

		bool addPackages = true;
	};
}