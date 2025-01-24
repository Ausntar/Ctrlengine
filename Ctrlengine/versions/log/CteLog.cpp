#include "CteLog.hpp"
namespace cte {
	auto CteLog::addLog() -> std::shared_ptr<spdlog::logger> {
		try {
			auto logger = spdlog::daily_logger_mt("logger", "../../logs/logs.txt", 2, 30);
			logger->flush_on(spdlog::level::info);
			return logger;
		}
		catch (const spdlog::spdlog_ex& ex) {
			spdlog::info("Log failed to initialize: {}", ex.what());
			return nullptr;
		}
	}
}