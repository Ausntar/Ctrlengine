#include "CteReadFile.hpp"
namespace cte {
	std::string CteReadFile::readFile(std::string file_path) {
		std::ifstream file(file_path);
		if (!file.is_open()) {
			spdlog::error("无法打开文件: {}", file_path);
			return FILE_ERROR;
		}
		std::string content;
		std::string line;
		while (std::getline(file, line)) {
			content += line + "\n";
		}
		file.close();
		return content;
	}
	std::string CteReadFile::readJson(std::string file,std::string find_setting) {
		try {
			std::ifstream i(file);
			json::json j;
			i >> j;
			return j[find_setting];
		}
		catch (json::json::parse_error& e) {
			spdlog::error("Json读取错误: {}", e.what());
			return FILE_ERROR;
		}
	}
	std::string CteReadFile::readSave(std::string file) {
		std::string content = readFile(file);
		if (content == FILE_ERROR) {
			return FILE_ERROR;
		}
		size_t pos = content.find("chapter:");
		if (pos != std::string::npos) {
			pos += 8;
			return content.substr(pos);
		}
		return FILE_ERROR;
	}
	std::vector<std::string> CteReadFile::readSave(std::string folder, int Type) {
		std::vector<std::string> files;
		std::string path = folder + "/*";
		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind = FindFirstFileA(path.c_str(), &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) {
			spdlog::error("无法打开文件夹: {}", folder);
			return files;
		}
		do {
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				continue;
			}
			std::string file = FindFileData.cFileName;
			if (Type == 0) {
				files.push_back(file);
			}
			else {
				std::string content = readFile(folder + "/" + file);
				if (content == FILE_ERROR) {
					continue;
				}
				size_t pos = content.find("chapter:");
				if (pos != std::string::npos) {
					pos += 8;
					files.push_back(content.substr(pos));
				}
			}
		} while (FindNextFileA(hFind, &FindFileData));
		FindClose(hFind);
		return files;
	}
}
