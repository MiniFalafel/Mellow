workspace "Mellow"
	architecture "x86_64"
	startproject "Sandbox"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	
-- Output directory for a given workspace
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Includes in a lookup
includeDirs = {}
includeDirs["spdlog"] = "Mellow/vendor/spdlog/include/"

project "Mellow"
	location "Mellow"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	pchheader "mwpch.h"
	pchsource "Mellow/src/mwpch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs {
		"%{prj.name}/src",
		"%{includeDirs.spdlog}"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines {
			"MW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "MW_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "MW_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "MW_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"Mellow/src",
		"%{includeDirs.spdlog}"
	}
	
	links {
		"Mellow"
	}
	
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "MW_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "MW_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "MW_DIST"
		runtime "Release"
		optimize "on"
