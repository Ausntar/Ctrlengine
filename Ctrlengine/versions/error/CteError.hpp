#pragma once
#include <string>
#define FILE_ERROR "AUV,�ļ��򲻿���"
namespace cte {
	class CteError {
	public:
		void popUpDialogBox(int level,std::string text,std::string title);
		void reportError(std::string errorType, std::string errorMessage);
	};
}
