#pragma once

#include<string>
#include<fstream>
#include<iostream>
#include<nlohmann/json.hpp>

#include "spdlog/spdlog.h"
using json = nlohmann::json;
namespace cte {
	class ReadJson
	{
	public:
		std::string readFile(std::string path);
		std::string readJson(std::string json, std::string find_setting);
	private:
		std::string file_path = "";
		std::string find_setting = "";
	};
} // namespace cte