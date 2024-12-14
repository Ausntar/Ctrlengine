#include "readJson.hpp"
using json = nlohmann::json;
namespace cte {
	std::string ReadJson::readFile(const std::string path) {
		std::ifstream file(path);
		if (!file.is_open()) {
			spdlog::error("File not found" + file_path);
			spdlog::info("无法打开文件" + file_path);
			throw std::runtime_error("File not found");
			return"";
		}
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		return content;
	}
	std::string ReadJson::readJson(std::string json_content, std::string find_setting) {
		json j = json::parse(json_content);
		try {
			std::cout << find_setting << ": " << j[find_setting] << std::endl;
            return j[find_setting];
		}
		catch (json::parse_error& e) {
            spdlog::info("Json解析错误: {}", e.what());
			throw std::runtime_error("Json parse error");
			return"";
		}
	}
}