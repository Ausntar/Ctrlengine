#include "CteVerify.hpp"

namespace cte {
    bool CteVerify::verify(std::string start_ID) {
        if (start_ID.find("EDF") == std::string::npos) {
            return false;
        }
        for (int i = 0; i < start_ID.size(); i++) {
            if (start_ID[i] >= '0' && start_ID[i] <= '9') {
                return false;
            }
        }
        const char* command = "verify.exe";
        int result = std::system(command);
		if (result == 0) {
			return true;
		}
		return false;
    }
}
