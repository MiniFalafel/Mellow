#pragma once

#include <memory>

// Detect Platform
#ifdef _WIN32
	#ifdef _WIN64
		#define MW_PLATFORM_WINDOWS
	#else
		#error "Win32 platform is not supported!"
	#endif
#endif

namespace Mellow {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}