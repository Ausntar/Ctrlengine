#include "CteError.hpp"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

namespace cte {
	void CteError::popUpDialogBox(int level, std::string text, std::string title) {
#ifdef _WIN32
		UINT uType;
		switch (level) {
			case 0:
				uType = MB_ICONINFORMATION;
				break;
			case 1:
				uType = MB_ICONWARNING;
				break;
			case 2:
				uType = MB_ICONERROR;
				break;
			default:
				uType = MB_ICONINFORMATION;
				break;
		}
		MessageBoxA(NULL, text.c_str(), title.c_str(), uType | MB_OK);
#else
		std::cerr << "Dialog Box [" << title << "]: " << text << std::endl;
#endif
	}

	void CteError::reportError(std::string errorType, std::string errorMessage) {
		std::cerr << "Error [" << errorType << "]: " << errorMessage << std::endl;
	}
}
