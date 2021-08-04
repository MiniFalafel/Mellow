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
	
project "Mellow"
	location "Mellow"
	kind "staticlib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/*.h",
		"%{prj.name}/src/*.cpp"
	}
	
	includedirs {
		"%{prj.name}/src"
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

project "Sandbox"
	location "Sandbox"
	kind "staticlib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	files {
		"%{prj.name}/src/*.h",
		"%{prj.name}/src/*.cpp"
	}
	
	includedirs {
		"%{prj.name}/src"
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
