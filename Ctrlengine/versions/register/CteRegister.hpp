#pragma once
#include <string>
#include "../readfile/CteReadFile.hpp"
#include "../file management/CteFileManagement.hpp"
#include "../error/CteError.hpp"
#include "register.hpp"
namespace cte {
	bool Registration = true;
	bool Annotation = false;
	class CteRegister
	{
	public:
		int registerFile(std::string path, std::string name,std::string submitter,int level);
		int registerMusic(std::string path, std::string name, std::string submitter);
		int registerModel(std::string path, std::string name, std::string submitter);
		int registerTexture(std::string path, std::string name, std::string submitter);
	};
}

