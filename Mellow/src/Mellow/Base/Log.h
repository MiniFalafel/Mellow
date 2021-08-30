#pragma once

#include "Mellow/Base/Base.h"

#include <spdlog/spdlog.h>

namespace Mellow {
	
	class Log {

	public:

		static void Init();

		static inline Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static inline Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

	};
}

// Logging macros
// Core
#define MW_CORE_TRACE(...)    ::Mellow::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define MW_CORE_INFO(...)     ::Mellow::Log::GetCoreLogger()->info(__VA_ARGS__);
#define MW_CORE_WARN(...)     ::Mellow::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define MW_CORE_ERROR(...)    ::Mellow::Log::GetCoreLogger()->error(__VA_ARGS__);
#define MW_CORE_CRITICAL(...) ::Mellow::Log::GetCoreLogger()->critical(__VA_ARGS__);
// Client
#define MW_TRACE(...)    ::Mellow::Log::GetClientLogger()->trace(__VA_ARGS__);
#define MW_INFO(...)     ::Mellow::Log::GetClientLogger()->info(__VA_ARGS__);
#define MW_WARN(...)     ::Mellow::Log::GetClientLogger()->warn(__VA_ARGS__);
#define MW_ERROR(...)    ::Mellow::Log::GetClientLogger()->error(__VA_ARGS__);
#define MW_CRITICAL(...) ::Mellow::Log::GetClientLogger()->critical(__VA_ARGS__);