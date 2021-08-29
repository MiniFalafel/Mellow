#pragma once

// Detect Platform
#ifdef _WIN32
	#ifdef _WIN64
		#define MW_PLATFORM_WINDOWS
	#else
		#error "Win32 platform is not supported!"
	#endif
#endif