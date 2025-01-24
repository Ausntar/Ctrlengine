#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include "../error/CteError.hpp"

namespace json = nlohmann;
namespace cte {
	class CteReadFile
	{
	public:
		std::string readFile(std::string file_path);
		std::string readJson(std::string file,std::string find_setting);

		std::string readSave(std::string file);
		std::vector<std::string> readSave(std::string folder,int Type);
	};
}


