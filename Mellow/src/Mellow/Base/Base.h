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

#define MW_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

// Assertions
#ifdef MW_DEBUG
	#define MW_ENABLE_ASSERTS
#endif

#ifdef MW_ENABLE_ASSERTS
	#define MW_CORE_ASSERT(x, ...) {if(!x) { MW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MW_ASSERT(x, ...) {if(!x) { MW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MW_CORE_ASSERT(x, ...)
	#define MW_ASSERT(x, ...)
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

// Bit Shifting
#define BSHIFT(x) 1 << x