#pragma once
#include <spdlog/spdlog.h>
#include "spdlog/sinks/daily_file_sink.h"
namespace cte
{
	class CteLog
	{
	public:
		std::shared_ptr<spdlog::logger> addLog();
	};
}
