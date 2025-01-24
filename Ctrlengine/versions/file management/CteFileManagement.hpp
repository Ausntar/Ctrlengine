#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "file/file/file.hpp"
#include "file/music/music.hpp"
#include "file/model/model.hpp"
#include "file/texture/texture.hpp"
#include "../readfile/CteReadFile.hpp"
#include "../error/CteError.hpp"
#include "../settings/CteManageSettings.hpp"
namespace cte {
	bool fileManagement = true;
	bool mark = false;
	std::vector<File> files;
	std::vector<Music> music;
	std::vector<Model> models;
	std::vector<TextureFile> texture;
	class CteFileManagement
	{
	public:
		int addFile(std::string path, std::string name, std::string submitter, int level);
		int addMusic(std::string path, std::string name, std::string submitter);
		int addModel(std::string path, std::string name, std::string submitter);
		int addTexture(std::string path, std::string name, std::string submitter);
	};
}


