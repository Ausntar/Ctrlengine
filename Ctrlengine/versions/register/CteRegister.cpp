#include "CteRegister.hpp"
namespace cte {
	bool enableRegistration() {
		CteReadFile readfile;
		std::string content = readfile.readFile("register.Json");
		if (content == FILE_ERROR) {
			CteError error;
			error.reportError("register.Json", "File_Error");
			return false;
		}
		try {
			std::string pd = readfile.readJson("register.Json", "register");
			if (pd == FILE_ERROR) {
				CteError error;
				error.reportError("register.Json", "File_Error");
				return false;
			}
			if (pd != "ture") {
				spdlog::warn("注册没有启用");
				return false;
			}
		}
		catch (json::json::parse_error& e) {
			spdlog::error("Json读取错误: {}", e.what());
			return false;
		}
	}
	int CteRegister::registerFile(std::string path, std::string name, std::string submitter, int level) {
		if(Annotation == false) {
			Registration = enableRegistration();
		}
		if (Registration != true) {
            return -1;
		}
		CteFileManagement FileManagement;
		int number = FileManagement.addFile(path, name, submitter, level);
		registerSubmitter.push_back(submitter);
		if (number == -1) {
			return -1;
		}
		return number;
	}
	int CteRegister::registerMusic(std::string path, std::string name, std::string submitter) {
		if (Annotation == false) {
			Registration = enableRegistration();
		}
		if (Registration != true) {
			return -1;
		}
		CteFileManagement FileManagement;
		int number = FileManagement.addMusic(path, name, submitter);
		registerSubmitter.push_back(submitter);
		if (number == -1) {
			return -1;
		}
		return number;
	}
	int CteRegister::registerModel(std::string path, std::string name, std::string submitter) {
		if (Annotation == false) {
			Registration = enableRegistration();
		}
		if (Registration != true) {
			return -1;
		}
		CteFileManagement FileManagement;
		int number = FileManagement.addModel(path, name, submitter);
		registerSubmitter.push_back(submitter);
		if (number == -1) {
			return -1;
		}
		return number;
	}
	int CteRegister::registerTexture(std::string path, std::string name, std::string submitter) {
		if (Annotation == false) {
			Registration = enableRegistration();
		}
		if (Registration != true) {
			return -1;
		}
		CteFileManagement FileManagement;
		int number = FileManagement.addTexture(path, name, submitter);
		registerSubmitter.push_back(submitter);
		if (number == -1) {
			return -1;
		}
		return number;
	}
}
