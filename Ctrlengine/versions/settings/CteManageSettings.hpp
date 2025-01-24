#pragma once
#include <string>
#include <spdlog/spdlog.h>
#include "../readfile/CteReadFile.hpp"
#include "settings.hpp"
namespace cte {
	EngineSettings settings;
	class CteManageSettings
	{
	public:
		bool refreshEngineSettings(std::string json_path);
	};
}


