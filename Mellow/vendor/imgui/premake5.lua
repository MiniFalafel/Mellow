project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputDir .. "%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "%{prj.name}")
	
	files {
		
		"imgui/imconfig.h",
		"imgui/imgui.cpp",
		"imgui/imgui.h",
		"imgui/imgui_demo.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_internal.h",
		"imgui/imgui_tables.cpp",
		"imgui/imgui_widgets.cpp",
		"imgui/imstb_rectpack.h",
		"imgui/imstb_textedit.h",
		"imgui/imstb_truetype.h"
		
	}
	
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		
	filter "system:linux"
		pic "on"
		systemversion "latest"
		cppdialect "C++17"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"