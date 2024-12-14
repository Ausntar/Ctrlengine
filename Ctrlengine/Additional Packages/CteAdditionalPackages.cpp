#include "CteAdditionalPackages.hpp"
using json = nlohmann::json;
namespace cte {
	std::vector<std::string> CteAdditionalPackages::readAdditionalPackage(std::string path = "/Packages") {
        std::string folderPath = path;
        std::vector<std::string> filenames;
        try {
            for (const auto& entry : fs::directory_iterator(folderPath)) {
                filenames.push_back(entry.path().filename().string());
            }
            for (const auto& filename : filenames) {
                std::cout << "   " << filename << std::endl;
            }
            spdlog::info("读取文件夹中的文件成功，共有 {} 个文件", filenames.size());
        }
        catch (const fs::filesystem_error& e) {
            spdlog::error("无法读取文件夹中的文件: {}", e.what());
            spdlog::warn("已禁用附加包");
            return;
        }
        return filenames;
	}
    void CteAdditionalPackages::addAdditionalPackage(std::string path) {
        cte::ReadJson reader;
        try {
            std::string jsonContent = reader.readFile(path + "/Package.json");
            std::string PackageName = reader.readJson(jsonContent, "PackageName");
            std::string PackageType = reader.readJson(jsonContent, "PackageType");


            if (PackageType == "addMusic") {
                jsonContent = jsonContent.substr(jsonContent.find("PackageType") + 11, jsonContent.length() - (jsonContent.find("PackageType") + 11));
                addMusic(path, jsonContent);
            }
            else if (PackageType == "addLanguage") {
                addLanguage(path);
            }
            else if (PackageType == "addPlayingMethod") {
                addPlayingMethod(path);
            }
            else if (PackageType == "addCode") {
                addCode(path);
            }
            else {
                spdlog::error("未知的附件包类型: {}", PackageType);
                return;
            }
        }
        catch (const std::exception& e) {
            spdlog::error("读取附加包信息时发生错误: {}", e.what());
            spdlog::warn("已禁用附加包");
            return;
        }
        return;
    }
    void CteAdditionalPackages::addMusic(std::string path,std::string jsonContent) {
        std::vector<std::string> music_path;
        fs::path directory_path(path);
        spdlog::info("正在加载音乐附加包: {}", directory_path.filename().string());
        for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (entry.is_regular_file()) {
                if (entry.is_regular_file() && entry.path().filename() != "Package.json") {
                    music_path.push_back(entry.path().filename().string());
                }
            }
        }
        MusicNumber.resize(64);
        spdlog::info("当前共有 {} 首音乐", music_path.size());
        cte::ReadJson reader;
        try {
            for (long long i = 0; jsonContent != ""; i++) {
                MusicNumber[i].music_name = reader.readJson(jsonContent, "MusicName");
                MusicNumber[i].music_path = reader.readJson(jsonContent, "MusicPath");
                MusicNumber[i].music_type = reader.readJson(jsonContent, "MusicType");
                MusicNumber[i].music_author = reader.readJson(jsonContent, "MusicAuthor");
            }
        }
        catch (json::parse_error& e) {
            spdlog::error("无法添加音乐附加包: {}", e.what());
            spdlog::warn("已禁用附加包");
        }
        return;
    }
    void CteAdditionalPackages::addLanguage(std::string path) {

    }
    void CteAdditionalPackages::addPlayingMethod(std::string path) {

    }
    void CteAdditionalPackages::addCode(std::string path) {

    }
}
