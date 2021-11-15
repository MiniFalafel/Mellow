#include "mwpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Mellow {
	
	// Logger references
	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		MW_PROFILE_FUNCTION();

		// Set logging pattern
		spdlog::set_pattern("%^[%T] %n: %v%$");
		// Create Core/Engine-side logger.
		s_CoreLogger = spdlog::stdout_color_mt("CORE");
		s_CoreLogger->set_level(spdlog::level::trace);
		// Create Application/Client-side logger
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}