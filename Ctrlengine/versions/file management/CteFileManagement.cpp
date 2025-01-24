#include "CteFileManagement.hpp"
namespace fs = std::filesystem;
namespace cte {
	bool fileExists(const std::string& filename) {
		fs::path filePath(filename);
		return fs::exists(filePath); // ����ļ��Ƿ����
	}
	bool enableFileManagement() {
		CteReadFile readfile;
		std::string content = readfile.readFile("file_management.Json");
		if (content == FILE_ERROR) {
			CteError error;
			error.reportError("file_management.Json", FILE_ERROR);
			return false;
		}
		try {
			std::string pd = readfile.readJson("file_management.Json", "file_management");
			if (pd == FILE_ERROR) {
				CteError error;
				error.reportError("file_management.Json", FILE_ERROR);
				return false;
			}
			if (pd != "ture") {
				spdlog::warn("�ļ�����û������");
				return false;
			}
		}
		catch (json::json::parse_error& e) {
			spdlog::error("Json��ȡ����: {}", e.what());
			return false;
		}
	}
	int CteFileManagement::addFile(std::string path, std::string name, std::string submitter, int level) {
		if (mark == false) {
			fileManagement = enableFileManagement();
			mark = true;
		}
		if (fileManagement == false) {
			return -1;
		}
		if (submitter == "Ctrlengine") {
			files.push_back({ path,name,submitter,level });
			return files.size();
		}
		if (settings.addPackages == true) {
			if (!fileExists(path)) {
				spdlog::error("�ļ�������: {}", path);
				return -1;
			}
			files.push_back({ path,name,submitter,level });
			return files.size();
		}
		
	}
	int CteFileManagement::addMusic(std::string path, std::string name, std::string submitter) {
		if (mark == false) {
			fileManagement = enableFileManagement();
			mark = true;
		}
		if (fileManagement == false) {
			return -1;
		}
		if (submitter == "Ctrlengine") {
			music.push_back({ path,name,submitter });
			return -1;
		}
		if (settings.addPackages == true) {
			if (!fileExists(path)) {
				spdlog::error("�ļ�������: {}", path);
				return music.size();
			}
			music.push_back({ path,name,submitter });
			return music.size();
		}
	}
	int CteFileManagement::addModel(std::string path, std::string name, std::string submitter) {
		if (mark == false) {
			fileManagement = enableFileManagement();
			mark = true;
		}
		if (fileManagement == false) {
			return -1;
		}
		if (submitter == "Ctrlengine") {
			models.push_back({ path,name,submitter });
			return models.size();
		}
		if (settings.addPackages == true) {
			if (!fileExists(path)) {
				spdlog::error("�ļ�������: {}", path);
				return -1;
			}
			models.push_back({ path,name,submitter });
			return models.size();
		}
	}
	int CteFileManagement::addTexture(std::string path, std::string name, std::string submitter) {
		if (mark == false) {
			fileManagement = enableFileManagement();
			mark = true;
		}
		if (fileManagement == false) {
			return -1;
		}
		if (submitter == "Ctrlengine") {
			texture.push_back({ path,name,submitter });
			return texture.size();
		}
		if (settings.addPackages == true) {
			if (!fileExists(path)) {
				spdlog::error("�ļ�������: {}", path);
				return -1;
			}
			texture.push_back({ path,name,submitter });
			return texture.size();
		}
	}
}
