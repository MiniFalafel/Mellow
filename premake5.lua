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
includeDirs["GLFW"] = "Mellow/vendor/GLFW/include/"
includeDirs["glad"] = "Mellow/vendor/glad/include/"
includeDirs["glm"] = "Mellow/vendor/glm/"
includeDirs["ImGui"] = "Mellow/vendor/imgui/imgui/"

-- Other premake files
include "Mellow/vendor/GLFW"
include "Mellow/vendor/glad"
include "Mellow/vendor/imgui"

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
		"%{includeDirs.spdlog}",
		"%{includeDirs.GLFW}",
		"%{includeDirs.glad}",
		"%{includeDirs.glm}",
		"%{includeDirs.ImGui}"
	}
	
	links {
		"GLFW",
		"glad",
		"ImGui"
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
		"%{includeDirs.spdlog}",
		"%{includeDirs.GLFW}",
		"%{includeDirs.glm}",
		"%{includeDirs.ImGui}"
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
