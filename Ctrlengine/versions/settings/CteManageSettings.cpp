#include "CteManageSettings.hpp"

namespace cte {
	bool CteManageSettings::refreshEngineSettings(std::string json_path) {
		std::string content = CteReadFile().readJson(json_path, "settings");
		if (content == FILE_ERROR) {
			return false;
		}
		try {
			json::json j = json::json::parse(content);
			settings.gameName = j["gameName"];
			settings.version = j["version"];
			settings.gameType = j["gameType"];
			settings.windowWidth = j["windowWidth"];
			settings.windowHeight = j["windowHeight"];
			settings.enableVsync = j["enableVsync"];
			settings.frameRate = j["frameRate"];
			settings.tick = j["tick"];
			settings.renderAPI = j["renderAPI"];
			settings.enableDebug = j["enableDebug"];
			settings.enableConsole = j["enableConsole"];
			settings.enableMouse = j["enableMouse"];
			settings.language = j["language"];
			settings.addPackages = j["addPackages"];
			return true;
		}
		catch (json::json::parse_error& e) {
			spdlog::error("Json∂¡»°¥ÌŒÛ: {}", e.what());
			return false;
		}
	}
	
}