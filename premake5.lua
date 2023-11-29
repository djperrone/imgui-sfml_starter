workspace "imgui-sfml_starter"
  architecture "x86"
  startproject "imgui-sfml_starter"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SFML"] = "imgui-sfml_starter/vendor/SFML/include"
IncludeDir["ImGui"] = "imgui-sfml_starter/vendor/imgui"
IncludeDir["ImGui_SFML"] = "imgui-sfml_starter/vendor/imgui-sfml"

include "imgui-sfml_starter/vendor/imgui"
include "imgui-sfml_starter/vendor/imgui-sfml"

project "imgui-sfml_starter"
  	location "imgui-sfml_starter"
    kind "ConsoleApp"
    language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{ 
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/imgui/*.h",
		"%{prj.name}/vendor/imgui/*.cpp",
		"%{prj.name}/vendor/imgui-sfml/*.h",
		"%{prj.name}/vendor/imgui-sfml/*.cpp"		
	}

	includedirs
	{		
		"%{IncludeDir.SFML}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui_SFML}",
		"%{prj.name}/vendor/spdlog/include"
	}

	libdirs
	{ 
		"imgui-sfml_starter/vendor/SFML/lib"
	}

	links
	{ 
		"opengl32.lib",
		"freetype.lib",
		"winmm.lib",
		"gdi32.lib",
		"openal32.lib",
		"flac.lib",
		"vorbisenc.lib",
		"vorbisfile.lib",
		"vorbis.lib",
		"ogg.lib",
		"ws2_32.lib",
		"ImGui",
		"ImGui_SFML"		
	}

filter "system:windows"
  cppdialect "C++17"
    systemversion "latest"

  defines {"SFML_STATIC" }

  filter "configurations:Debug"			
		runtime "Debug"	
		symbols "on"
		links { "sfml-audio-s-d.lib", "sfml-graphics-s-d.lib", "sfml-network-s-d.lib", "sfml-system-s-d.lib", "sfml-window-s-d.lib" }

	filter "configurations:Release"			
		runtime "Release"
		optimize "on"
	
		links { "sfml-audio-s.lib", "sfml-graphics-s.lib", "sfml-network-s.lib", "sfml-system-s.lib", "sfml-window-s.lib" }
 
  