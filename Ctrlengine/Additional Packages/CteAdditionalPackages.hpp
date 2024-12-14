#pragma once
#include <string>
#include <filesystem>
#include <iostream>
#include <vector>

#include "../ReadJson/readJson.hpp"
#include "../Music/Music.hpp"
#include "spdlog/spdlog.h"

namespace fs = std::filesystem;
namespace cte {
	class CteAdditionalPackages
	{
	public:
		std::vector<std::string> readAdditionalPackage(std::string path="/Packages/");
        void addAdditionalPackage(std::string path);
		void addMusic(std::string path, std::string jsonContent);
		void addLanguage(std::string path);
		void addPlayingMethod(std::string path);
		void addCode(std::string path);
	};
}

